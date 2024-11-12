cmake_minimum_required(VERSION 3.15.0)

project(EigenMVR VERSION 1.0.0)

# include the search for Eigen
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/vendor")
include(${CMAKE_CURRENT_LIST_DIR}/vendor/eigen.CMakeLists.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/vendor/FindLAPACKE.cmake)

find_package(LAPACKE REQUIRED)

add_executable(test test.cpp)

target_link_libraries(test PUBLIC Eigen3::Eigen ${LAPACKE_LIBRARIES})
