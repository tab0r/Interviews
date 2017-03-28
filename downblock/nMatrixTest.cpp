#include <cassert>
#include <iostream>
#include "nMatrix.h"
#include <vector>

typedef std::vector<unsigned int> nat_vect;

using namespace std;

int main () {
	
	int n =4;

	// Create a 3D array
	nMatrix matrix(n);
	int extents[] = {3,3,3,3};
	matrix.setDims(extents);

	// n-dimensional iterator
	int values = 0;
	// zero n-vector to store current coords
	int coords[matrix.getDim()];
	for (int i = 0; i != matrix.getDim(); i++) {
		coords[i] = 0;
		};
		
	// for the number of elements, iterate the current coords
	for (int i = 0; i < matrix.size(); i ++) {	
		// do something with the current coords here
		
		matrix.put(coords, values++);
		
		// handy debugging output
		/*
		cout << i << ": Iterator coords: ";
		for (int d = 0; d != matrix.getDim(); d++) {
			cout << coords[d];
			if (d != matrix.getDim()-1) cout << ", ";
			} cout << endl;
		*/
		
		// prepare for the next iteration
		
		// add to the first dimension
		coords[0] = coords[0] + 1;
		
		// check dimensions, if we reach the end of one, reset
		// and iterate the next
		for (int d = 0; d != matrix.getDim(); d++) {
			// if we're at the end of a dimension
			if (coords[d] == matrix.getExtent(d)) {
				coords[d+1] = coords[d+1] + 1;
				coords[d] = 0;
				}
			}
		}

	// Verify values 
	/*
	int verify = 0;
	for(int i = 0; i != 2; ++i) 
		for(int j = 0; j != 4; ++j)
			for(int k = 0; k != 8; ++k)	 {
				int coords[] = {k, j, i};
				assert(matrix.grab(coords) == verify++);
				cout << "Value at coords {" << k << ", " << j << ", " << i << "} in nMatrix: " << matrix.grab(coords);// << endl;
				cout << " has index " << matrix.coordsToIdx(coords) << endl;
				}; 
	*/
	matrix.displayVectors(); 
	return 0;
}