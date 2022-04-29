#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "KDTree.hpp"


template <size_t N, typename IteratorType>
Point<N> point_from_range(IteratorType begin, IteratorType end) {
  Point<N> result;
  std::copy(begin, end, result.begin());
  return result;
}

Point<1> make_point(double x) {
  Point<1> result;
  result[0] = x;
  return result;
}
Point<2> make_point(double x, double y) {
  Point<2> result;
  result[0] = x;
  result[1] = y;
  return result;
}
Point<3> make_point(double x, double y, double z) {
  Point<3> result;
  result[0] = x;
  result[1] = y;
  result[2] = z;
  return result;
}
Point<4> make_point(double x, double y, double z, double w) {
  Point<4> result;
  result[0] = x;
  result[1] = y;
  result[2] = z;
  result[3] = w;
  return result;
}


int main() {
  const double data_points[][4] = {
      {0, 0, 0, 0},  // 0
      {0, 0, 0, 1},  // 1
      {0, 0, 1, 0},  // 2
      {0, 0, 1, 1},  // 3
      {0, 1, 0, 0},  // 4
      {0, 1, 0, 1},  // 5
      {0, 1, 1, 0},  // 6
      {0, 1, 1, 1},  // 7
      {1, 0, 0, 0},  // 8
      {1, 0, 0, 1},  // 9
      {1, 0, 1, 0},  // 10
      {1, 0, 1, 1},  // 11
      {1, 1, 0, 0},  // 12
      {1, 1, 0, 1},  // 13
      {1, 1, 1, 0},  // 14
      {1, 1, 1, 1},  // 15
  };
  
  KDTree<4> kd;
  for (size_t i = 0; i < 16; ++i)
    kd.insert(point_from_range<4>(data_points[i], data_points[i] + 4), i);

  for (size_t i = 0; i < 16; ++i){ 
      cout<<"node: ";
      for(int j = 0; j< 4; j++){
        cout << data_points[i][j]<< " ";
      }
      cout<<" vecino mas cercano "<<kd.knn(point_from_range<4>(data_points[i], data_points[i] + 4),
                    1)<<endl;
  }
}
