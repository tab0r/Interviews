#include <iostream>
#include <array>
#include <math.h>
#include <vector>
#include "nMatrix.h"

using namespace std;

typedef std::vector<unsigned int> nat_vect;

class downSampleS {
	public:
		//void loadImage(filename file);
		downSampleS();
		unsigned int maxl;
		void loadImage();
		void makeTest(int p);
		void downSample(int l);
		void downSample(int l, bool debugSwitch);
	private:
		unsigned int imgDim;
		//nat_vect imgDims;
		nMatrix oImage;
		int findMode(int array[], int size);
		void testMode(int numtests);
};

//#include "downSampleS.h"

// members

downSampleS::downSampleS():oImage(1) {                // constructor
	cout << "downsample set created\n"; // prints 
	// input test image dimensions
	cout << "Enter the number of dimensions for the images in the set.\n";
	cin >> imgDim;
	//imgDim = 2;
	oImage.setDim(imgDim);
	
	int dimArray[imgDim];
	for (int i = 0; i < imgDim; i++) {
		cout << "Enter a value for the extent of dimension " << i+1 << ": ";
		//unsigned int val;
		cin >> dimArray[i];//val;
		//imgDims.push_back(val);
		//oImage.setDims(i, val);
		};
		oImage.setDims(dimArray);
	cout << "The image will have " << oImage.size() << " pixels.\n";
	
	//oImage.values.assign(oImage_num_elems, 0);
   
	// calculate possible downsamplings
	maxl = log2(oImage.getExtent(0));
	for (int i=1; i < imgDim; i++) {
		if (log2(oImage.getExtent(i)) < maxl) {
			maxl = log2(oImage.getExtent(i));
			}
		}
		
	cout << "There are " << maxl << " downsamplings." << endl;
	}

void downSampleS::loadImage() {
	// load an image from a file, save to oImage
	}
	
void downSampleS::makeTest(int p) {
	
	/* initialize random seed: */
   //srand (std::time(NULL));
   int numVals = p;	  

	cout << "Creating a " << imgDim << " dimensional test image with " << numVals << " possible pixel values." << endl;
	// for each dimension, iterate through placing a random int (up to numVals) in each location
	// n-dimensional iterator
	// zero n-vector to store current coords
	int coords[imgDim];
	for (int i = 0; i != imgDim; i++) {
		coords[i] = 0;
		};
		
	// for the number of elements, iterate the current coords
	for (int i = 0; i < oImage.size(); i ++) {	
		// place the random value in the pixel
		oImage.put(coords, rand() % numVals);
		
		//cout << oImage.grab(coords);
		// handy debugging output
		/*
		cout << i << ": Iterator coords: ";
		for (int d = 0; d != oImage.getDim(); d++) {
			cout << coords[d];
			if (d != oImage.getDim()-1) cout << ", ";
			} cout << endl;
		*/
		
		// prepare for the next iteration
		
		// add to the first dimension
		coords[0] = coords[0] + 1;
		
		// check dimensions, if we reach the end of one, reset
		// and iterate the next
		for (int d = 0; d != oImage.getDim(); d++) {
			// if we're at the end of a dimension
			if (coords[d] == oImage.getExtent(d)) {
				coords[d+1] = coords[d+1] + 1;
				coords[d] = 0;
				}
			}
		}
		//oImage.displayVectors();
	}


void downSampleS::downSample(int l) {
	downSample(l, false);
	}
	
void downSampleS::downSample(int l, bool debugSwitch) { 
   
   // return l-downsampled images
   // calculate dimensions of downsampled images
   int newImgDims[imgDim];
	   for (int j = 0; j < imgDim; j++) {
			newImgDims[j] = fmax(1, oImage.getExtent(j)/pow(2,l));
			}
			
   // prepare new l-downsampled image
   
	cout << l << " downsampled image\n";
	nMatrix nImage(imgDim);
	nImage.setDim(imgDim);
	nImage.setDims(newImgDims);
	if (debugSwitch == true) {
		cout << "New image has dimensions {";
		for (int d = 0; d != imgDim; d++) {
				cout << nImage.getExtent(d);
				if (d != imgDim-1) cout << ", ";
				} cout << "}." << endl;
			}
	int blocksize = pow(2, l);
	if (debugSwitch == true) cout << "Image blocksize: " << blocksize << endl;
	
	// for every pixel in the new image, use blocksize & coordsToIdx to
	// get values for the mode

	// n-dimensional iterator
	// zero n-vector to store current coords
	// IN THE NEW IMAGE
	int coords[imgDim];
	for (int i = 0; i != imgDim; i++) {
		coords[i] = 0;
		};
		
	// for the number of elements, iterate the current coords
	for (int i = 0; i < nImage.size(); i ++) {	
		
		// to obtain mode, we'll have to place another n-dim iterator here
		// need offsets for dimensions
		if (debugSwitch == true) {
			cout << "Finding value for nImage coordinates {";
			for (int d = 0; d != imgDim; d++) {
				cout << coords[d];
				if (d != nImage.getDim()-1) cout << ", ";
				} cout << "}." << endl;
				}

		int blockCount = pow(blocksize, imgDim);
		int blockVec[blockCount];
		// calculate mode - time for another n-dim iterator
		
		// n-dimensional iterator
		
		// base n-vector to store current coords in nImage
		// this will than map into the oImage somewhere
		// and we iterate from that coordinate 
		// along each dimension, for the blocksize
		int blockCoords[imgDim];
		for (int i = 0; i < imgDim; i++) {
			int val = coords[i]*blocksize;
			blockCoords[i] = val;
			};
		
		// for the number of elements, iterate the current coords
		for (int i = 0; i < blockCount; i ++) {	
			// do something with the current coords here
			
			if (debugSwitch == true) {
				cout << "Grabbing value from oImage coordinates {";
				for (int d = 0; d != imgDim; d++) {
					cout << blockCoords[d];
					if (d != imgDim-1) cout << ", ";
					} cout << "}. ";// << endl;
				}
			blockVec[i] = oImage.grab(blockCoords);
			if (debugSwitch == true) cout << blockVec[i] << endl;
			// prepare for the next iteration
			// add to the first dimension
			blockCoords[0] = blockCoords[0] + 1;
		
			// check dimensions, if we reach the end of one, reset
			// and iterate the next
			for (int d = 0; d != imgDim; d++) {
				// if we're at the end of a dimension
				if (blockCoords[d]-coords[d]*blocksize == blocksize) {
					blockCoords[d+1] = blockCoords[d+1] + 1;
					blockCoords[d] = coords[d]*blocksize;
					}
				}
			}
		
		// calculate mode from blockVec
		
		int mode = findMode(blockVec, pow(blocksize, imgDim));
		if (debugSwitch == true) cout << "mode: " << mode << endl;
		// place the mode value in the pixel
		nImage.put(coords, mode);
		
		//cout << oImage.grab(coords);
		// handy debugging output
		/*
		cout << i << ": Iterator coords: ";
		for (int d = 0; d != oImage.getDim(); d++) {
			cout << coords[d];
			if (d != oImage.getDim()-1) cout << ", ";
			} cout << endl;
		*/
		
		// prepare for the next iteration
		
		// add to the first dimension
		coords[0] = coords[0] + 1;
		
		// check dimensions, if we reach the end of one, reset
		// and iterate the next
		for (int d = 0; d != imgDim; d++) {
			// if we're at the end of a dimension
			if (coords[d] == nImage.getExtent(d)) {
				coords[d+1] = coords[d+1] + 1;
				coords[d] = 0;
				}
			}
		}
		//nImage.displayVectors();
		nImage.clearData();	
	
   // prepare new images
   // currently this code only works for 2-dim images.
   // implement it n-dimensionally with the n-dim iterator! 4/12/16
	/*
		cout << l << " downsampled image\n";
		int newX = newImgDims[0];
		int newY = newImgDims[1];
		int nImage[newX][newY];
		cout << "New image has dimensions " << newX << " by " << newY << endl;
		int blocksize = pow(2, l);
		cout << "Image blocksize: " << blocksize << endl;
		for (int j = 0; j < newX; j++) {
			for (int k = 0; k < newY; k++) {
				//find (j,k)-block of oImage, store in array, store mode in nImage
				//cout << "Finding value for downsample coordinates (" << j << ", " << k << ").\n"; //debugging output line
				int blockCount = pow(blocksize, 2);
				int blockVals[blockCount];
				// iterate through block to get blockVals
				for (int w = 0; w < blocksize; w++) {
					for (int u = 0; u < blocksize; u++) {
						int blockIdx = blocksize*w+u;
						int XoIidx = j*blocksize+w;
						int YoIidx = k*blocksize+u;
						blockVals[blockIdx] = oImage.values.at(XoIidx+oImage.getExtent(0)*YoIidx);		
						// debugging output line
						//cout << blockIdx << ": " << blockVals[blockIdx] << " from oImage coords (" << XoIidx << ", " << YoIidx << ")." << endl;								
						}
					}
				nImage[j][k] = findMode(blockVals, pow(blocksize, 2));
				cout << nImage[j][k];; // <<endl;
				if (k+1 < newY) {cout << ", ";} else {cout << endl;};
				}			
			}*/
	}

// note that this mode function returns the lowest mode found

int downSampleS::findMode(int array[], int size) {
	sort(array, array + size);
//	cout << "Sorted Array looks like this." << endl;
	
	int number = array[0];
	int mode = number;
	int count = 1;
	int countMode = 1;
	
    //for (size_t i = 0; i != size; ++i) cout << array[i] << " "; 
    //cout << endl;
	for (int i=1; i<size; i++)
	{
    	  if (array[i] == number) 
    	  { // count occurrences of the current number
    	     count++;
    	     if (count > countMode) 
    	        {
    	              countMode = count; // mode is the biggest ocurrences
    	              mode = number;
    	        }
    	  }
    	  else
    	  { // now this is a different number
    	        if (count > countMode) 
    	        {
    	              countMode = count; // mode is the biggest ocurrences
    	              mode = number;
    	        }
    	       count = 1; // reset count for the new number
    	       number = array[i];
  		}
	}
//	cout << "Final mode is: " << mode << endl;
	return mode;
}

void downSampleS::testMode(int numtests) {
	for (int i = 0; i < numtests; i++) {
		int Args[10];
		cout << "mode of ";
		for (int j = 0; j < 10; j++) {
			Args[j] = rand() % 4;
			cout << Args[j] << ", ";
			};
	int mode = findMode(Args, sizeof(Args)/sizeof(Args[0]));
	cout << " is " << mode << endl;
	}
}