// requires vector

#include "nMatrix.h"
#include <iostream>

using namespace std;
	
nMatrix::nMatrix(int d) {
	//dimension = d;
	//dimensions.assign(d, 1);
	dimsSet = false;
	}

void nMatrix::setDim(int d) {
	dimension = d;
	dimsSet = false;
	}
	
void nMatrix::setDims(int dim, int extent) {
	if (dim < dimension) {  // verify dimension is in range
		dimensions[dim] = extent;
		}
	else {
		cout << "Dimension error\n";
		}
	}
	
void nMatrix::setDims() {
	dimsSet = true;
	}
	
void nMatrix::setDims(int *dims) {
	setDims(dims, false);
	}
	
void nMatrix::setDims(int *dims, bool debugSwitch) {
	int prod = 1;
	for (int i = 0; i < dimension; i++) {
		if (debugSwitch == true) cout << "Setting dimension " << i << " to " << dims[i] <<endl;
		dimensions.push_back(dims[i]);
		prod = prod * dims[i];
		}
	if (debugSwitch == true) cout << "nMatrix vector has " << prod << " entries.\n";
	values.assign(prod, 0);
	numEntries = prod;
	dimsSet = true;
	}
	
int nMatrix::getExtent(int d) {
	return dimensions.at(d);
	}
	
int nMatrix::getDim() {
	return dimension;
	}
	
int nMatrix::size() {
	return numEntries;
	}

int nMatrix::coordsToIdx(int *coords) {
	/* Debugging block
	cout << "Received coords: {";
	for (int i= 0; i < dimension; i++) {
		cout << coords[i];
		if (i != dimension - 1) cout << ", ";
		}
	cout << "}" << endl;*/
	
	if (dimsSet == false) {
		cout << "Cannot compute while dimensions not fixed.\n";
		return -1;
		}
	
	int index = coords[0];
	//cout << "First dim: " << index << endl;
	if (dimension >= 2) {
		for (int i = 1; i < dimension; i++) {
			if (coords[i] > 0) {
				int product = 1;
				for (int j = 0; j < i; j++) {
					product = product*dimensions[j];
					//cout << "product: " << product << endl;
					};
				index = index + product*(coords[i]);
				};
			};
		}
	//cout << "index: " << index << endl;
	return index;			
	}
		
int nMatrix::grab(int *coords) {
	if (dimsSet == false) {
		cout << "Cannot compute while dimensions not fixed.\n";
		return -1;
		}
	int idx = coordsToIdx(coords);
	return values.at(idx);
	}

void nMatrix::put(int *coords, int val) {
	put(coords, val, false);
	}

void nMatrix::put(int *coords, int val, bool debugSwitch) {
	
	int idx = coordsToIdx(coords);
	values.at(idx) = val;
	
	if (debugSwitch == true) {
		if (dimsSet == false) {
			cout << "Cannot compute while dimensions not fixed.\n";
			return;
			}
		cout << "Saving " << val << " at " << idx << endl;
		}
	}
	
void nMatrix::put(int val) {
	values.push_back(val);
	}
	
void nMatrix::displayVectors() {
	// print the nMatrix as a collection of row vectors
	// so a 4x4 matrix will display as 4 vectors
	// a 4x4x4 matrix will display as 4 groups of 4 vectors
	// a 4x4x4x4 matrix will display as 4 groups of 4 groups of 4 vectors
	// so if we vectorize along the first dimension, chunks of output will come 
	// along the final dimension
	
	int vectLength = dimensions[0];
	cout << "Printing vector view of nMatrix with vector length " << vectLength << endl;
	
	// n-dimensional iterator
	int values = 0;
	// zero n-vector to store current coords
	int coords[getDim()];
	for (int i = 0; i != getDim(); i++) {
		coords[i] = 0;
		};
		
	// for the number of elements, iterate the current coords
	for (int i = 0; i < size(); i ++) {	
		// do something with the current coords here
		
		//matrix.put(coords, values++);
		cout << grab(coords);
		
		// handy debugging output
		/*
		cout << i << ": Iterator coords: ";
		for (int d = 0; d != matrix.getDim(); d++) {
			cout << coords[d];
			if (d != matrix.getDim()-1) cout << ", ";
			} cout << endl;
		*/
		
		// prepare for the next iteration
		
		if (coords[0]+1 != getExtent(0)) {
			cout << ", ";
			} else {
			cout << endl;
			}
		
		// add to the first dimension
		coords[0] = coords[0] + 1;
		
		// check dimensions, if we reach the end of one, reset
		// and iterate the next
		for (int d = 0; d != getDim(); d++) {
			// if we're at the end of a dimension
			if (coords[d] == getExtent(d)) {
				coords[d+1] = coords[d+1] + 1;
				coords[d] = 0;
				
				cout << "~" << endl;
				}
			}
		}
			
	}
	
void nMatrix::clearData() {
	values.clear();
	}