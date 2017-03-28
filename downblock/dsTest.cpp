#include "downSampleS.cpp"

int main() {  
	downSampleS dsSet;
	int pix;
	cout << "Enter a value for the range of an individual pixel: " << endl;
	cin >> pix;
	dsSet.makeTest(pix);
	int maxl = dsSet.maxl;
	for (int i = 1; i <= maxl; i++) { 
		dsSet.downSample(i);
		}
	return 0;
	}