#include "boost/multi_array.hpp"
//#include <cassert>
#include <iostream>
#include "nMatrix.h"

using namespace std;

int main () {
  // Create a 3D array that is 3 x 4 x 2
  typedef boost::multi_array<double, 3> array_type;
  typedef array_type::index index;
  array_type A(boost::extents[2][4][8]);

  nMatrix matrix(3);
  int extents[] = {2,4,8};
  matrix.setDims(extents);

  // Assign values to the elements
  int values = 0;
  for(int i = 0; i != 2; ++i) 
    for(int j = 0; j != 4; ++j)
      for(int k = 0; k != 8; ++k)  {
       	int coords[] = {i, j, k};
       	//cout << "At " << i << ", " << j << ", " << k << endl;
       	//cout << "nMatrix index is " << matrix.coordsToIdx(coords) << endl;
        //cout << "Storing " << values << " in 3D array and nMatrix.\n";
        matrix.put(coords, values);
        A[i][j][k] = values++;
        }

  // Verify values
  //int verify = 0;
  for(int i = 0; i != 2; ++i) 
    for(int j = 0; j != 4; ++j)
      for(int k = 0; k != 8; ++k)  {
        //assert(A[i][j][k] == verify++);
        int coords[] = {i, j, k};
        cout << "Value at coords {" << i << ", " << j << ", " << k << "} in A: " << A[i][j][k] << endl;
        cout << "Value at coords {" << i << ", " << j << ", " << k << "} in nMatrix: " << matrix.grab(coords);// << endl;
        cout << "index " << matrix.coordsToIdx(coords) << endl;
        };

/*
	// 2D test
  nMatrix matrix(2);
  int extents[] = {2,2};
  matrix.setDims(extents);

  // Assign values to the elements
  int values = 0;
  for(int i = 0; i != 2; ++i) 
    for(int j = 0; j != 2; ++j) {
       	int coords[] = {i, j};
       	//cout << "At " << i << ", " << j << ", " << k << endl;
       	//cout << "nMatrix index is " << matrix.coordsToIdx(coords) << endl;
        //cout << "Storing " << values << " in 3D array and nMatrix.\n";
        matrix.put(coords, values);
        A[i][j] = values++;
        }

  // Verify values
  //int verify = 0;
  for(int i = 0; i != 2; ++i) 
    for(int j = 0; j != 2; ++j) {
        //assert(A[i][j][k] == verify++);
        int coords[] = {i, j};
        cout << "Value at coords {" << i << ", " << j << "} in A: " << A[i][j] << endl;
        cout << "Value at coords {" << i << ", " << j << "} in nMatrix: " << matrix.grab(coords) << endl;
        //cout << "The index in nMatrix was " << matrix.coordsToIdx(coords) << endl;
        };
*/
/* 4D test
  nMatrix matrix(4);
  int extents[] = {2,2,2,2};
  matrix.setDims(extents);

  // Assign values to the elements
  int values = 0;
  for(int i = 0; i != 2; ++i) 
    for(int j = 0; j != 2; ++j)
      for(int k = 0; k != 2; ++k) 
        for(int l = 0; l != 2; ++l) {
       	int coords[] = {i, j, k, l};
       	//cout << "At " << i << ", " << j << ", " << k << endl;
       	//cout << "nMatrix index is " << matrix.coordsToIdx(coords) << endl;
        //cout << "Storing " << values << " in 3D array and nMatrix.\n";
        matrix.put(coords, values);
        A[i][j][k][l] = values++;
        }

  // Verify values
  //int verify = 0;
  for(int i = 0; i != 2; ++i) 
    for(int j = 0; j != 2; ++j)
      for(int k = 0; k != 2; ++k) 
       for(int l = 0; l != 2; ++l) {
        //assert(A[i][j][k] == verify++);
        int coords[] = {i, j, k, l};
        cout << "Value at coords {" << i << ", " << j << ", " << k << ", " << l << "} in A: " << A[i][j][k][l] << endl;
        cout << "Value at coords {" << i << ", " << j << ", " << k << ", " << l << "} in nMatrix: " << matrix.grab(coords) << endl;
        //cout << "The index in nMatrix was " << matrix.coordsToIdx(coords) << endl;
        }; */
	matrix.displayVectors();
  return 0;
}