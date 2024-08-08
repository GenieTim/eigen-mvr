#include <Eigen/Dense>
#include <iostream>

int main(int argc, char const *argv[]) {
  srand((unsigned int) time(0));
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <size>" << std::endl;
    return 1;
  }
  /* code */
  int size = std::stoi(argv[1]);
  if (size < 3) {
    return 2;
  }

  Eigen::VectorXd r = Eigen::VectorXd::Random(size);
  Eigen::VectorXd z = Eigen::VectorXd::Zero(size);

  Eigen::ArrayXi indices = Eigen::ArrayXi(3);
  indices << 0, 1, size - 1;

  Eigen::Vector3d r3 = Eigen::Vector3d::Random();

  std::cout << "Whatevers\n"
            << (z(indices) + r(indices) - r3).squaredNorm() << std::endl;

  return 0;
}
