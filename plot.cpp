#include "tgaimage.h"
using namespace std;
#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <iostream>
#include <fstream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void plot(vector<int> rowptr, vector<int> colidx, vector<double> values) {
	
	int size = rowptr.size() - 1;
	int i = 0;
	TGAImage image(size, size, TGAImage::RGB);
	for (int row = 0; row < size; row++) {
		for (int k = 0; k < (rowptr[row + 1] - rowptr[row]); k++) {
			cout << row << " " << colidx[i] << endl;
			image.set(colidx[i],size -1 -row, red);
			i++;
		}

	}
	image.flip_vertically();
	image.write_tga_file("output.tga");
}
int main() {
	vector<int> rowptr = { 0,2,5,5,7,7,10 }, colidx = {0,1,0,2,3,0,4,2,3,5};
	vector<double> values = { 0.3, 1.4, 5.7, 2.4, 9.5, 3.3, 8.1, 1.1, 2.6, 4.5 };
	plot(rowptr, colidx, values);
	return 0;


}


