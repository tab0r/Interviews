#include <vector>

typedef std::vector<unsigned int> nat_vect;

class nMatrix {
	public:
		nMatrix(int d);
		nat_vect values; // should probly be private, leaving public for now
		void setDim(int d);
		void setDims(int dim, int extent=1);
		void setDims(int *dims, bool debugSwitch);
		void setDims(int *dims);
		void setDims();
		int getExtent(int d);
		int getDim();
		int size();
		int coordsToIdx(int *coords);
		int grab(int *coords);
		void put(int *coords, int val);
		void put(int val);
		void put(int *coords, int val, bool debugSwitch);
		void displayVectors();
		void clearData();
	private:
		int dimension;
		nat_vect dimensions;
		int numEntries;
		bool dimsSet;
	};