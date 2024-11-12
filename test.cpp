#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <complex>
#define lapack_complex_float std::complex<float>
#define lapack_complex_double std::complex<double>
#include <iostream>
#include <algorithm>

int main(int argc, char const *argv[]) {
  srand((unsigned int)time(0));
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <size> <size>" << std::endl;
    return 1;
  }
  /* code */
  int size = std::stoi(argv[1]);
  size_t nRows = size;
  int size2 = std::stoi(argv[2]);
  if (size < 3) {
    return 2;
  }

  bool includeEigenvectors = true;

  std::vector< Eigen::Triplet<double> > triplets;
  triplets.reserve(size2 * 2);
  for (int i = 0; i < size2 * 2; ++i) {
    triplets.push_back(
        Eigen::Triplet<double>(i % size, std::max<int>(0, (i - 2) % size),
                               static_cast<double>(rand()) / RAND_MAX));
  }
  Eigen::SparseMatrix<double> sparseA =
      Eigen::SparseMatrix<double>(nRows, nRows);
  sparseA.setFromTriplets(triplets.begin(), triplets.end());

  Eigen::MatrixXd A = Eigen::MatrixXd(sparseA);
  Eigen::VectorXd eigenvaluesMemory = Eigen::VectorXd::Zero(nRows);
  Eigen::MatrixXd eigenvectorsMemory = includeEigenvectors
                                           ? Eigen::MatrixXd::Zero(nRows, nRows)
                                           : Eigen::MatrixXd::Zero(nRows, 3);
  int il = 0;
  int iu = 0;
  double abstol = 1e-10;
  int M = 0;

  Eigen::VectorXi support = Eigen::VectorXi::Zero(nRows * 2);

  int info = LAPACKE_dsyevr(Eigen::MatrixXd::IsRowMajor
                                ? LAPACK_ROW_MAJOR
                                : LAPACK_COL_MAJOR,          // matrix_order
                            includeEigenvectors ? 'V' : 'N', // JOBZ
                            'A',                             // RANGE
                            'U',                             // UPLO
                            nRows,                           // N
                            A.data(), // A
                            nRows,                                   // LDA
                            0,                                       // VL
                            0,                                       // VU
                            il,                                      // IL
                            iu,                                      // IU
                            abstol,                                  // ABSTOL
                            &M, // M, total number of eigenvalues found
                            eigenvaluesMemory.data(),  // W
                            eigenvectorsMemory.data(), // Z
                            eigenvectorsMemory.cols(), // LDZ
                            support.data()             // ISUPPZ
  );

  std::cout << "Eigenvalues: " << eigenvaluesMemory.transpose() << std::endl;
  if (includeEigenvectors) {
    std::cout << "Eigenvectors: " << eigenvectorsMemory << std::endl;
  }

  return 0;
}
