#include "tgaimage.h"
using namespace std;
#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <iostream>
#include <fstream>
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
TGAColor color(double value, double max, double min) {
	int fun = round((1020/(max-min)) *( value - min));
	int k = fun / 255;
	if (k == 0) return  TGAColor(0, (fun % 255), 255, 255);
	else if (k == 1) return  TGAColor(0, 255,255-(fun % 255), 255);
	else if (k ==2 ) return  TGAColor(255- (fun % 255),255, 0, 255);
	else if (k==3) return  TGAColor(255, 255 - (fun % 255),0, 255);
	else return  TGAColor(255, 0, 0, 255);

}

void plot(int* ptr, int* y, double* data, int n, double max, double min) {
	//vector<int> rowptr = { 0,2,5,5,7,7,10 }, colidx = {0,1,0,2,3,0,4,2,3,5};
	//vector<double> values = { 0.3, 1.4, 5.7, 2.4, 9.5, 3.3, 8.1, 1.1, 2.6, 4.5 };
	int size = n;//rowptr.size() - 1;
	int i = 0;
	int value=0;
	TGAImage image(size, size, TGAImage::RGB);
	for (int row = 0; row < size; row++) {
		for (int k = 0; k < (ptr[row + 1] - ptr[row]); k++) {
			cout << row << " " << y[i] << endl;
			image.set(y[i], size - row - 1, color(data[value],max, min));
			value++;
			i++;
		}

	}
	image.flip_vertically();
	image.write_tga_file("output.tga");
}

int main()
{
	ifstream in;
	in.open("input.mtx");
	int row = 0, col = 0, n = 0;
	in >> row >> col >> n;


	int* x = new int[n];
	int* y = new int[n];
	double* data = new double[n];

	double max_abs = 0;
	in >> x[0] >> y[0] >> data[0];
	x[0]--;
	y[0]--;
	double min = data[0];
	double max = data[0];
	for (int i = 1; i < n; ++i) {
		in >> x[i] >> y[i] >> data[i];
		x[i]--;
		y[i]--;

		if (abs(data[i]) > max_abs) max_abs = abs(data[i]);
		if (data[i] > max) max = data[i];
		else if (data[i] < min) min = data[i];


	}
	
	int value = row + 1;

	int* ptr = new int[value];
	int prevx = 0;

	for (int i = 0; i < value; i++)
	{
		ptr[i] = 0;
	}

	ptr[0] = 0;
	for (int i = 0; i < n; i++)
	{
		ptr[y[i] + 1] += 1;
	}

	for (int i = 0; i < row; i++)
	{
		ptr[i + 1] += ptr[i];
	}

	cout << "row = " << row << " col = " << col << " n = " << n << endl;

	//for (int i = 0; i < value; ++i) {
	//	cout << ptr[i] << " ";
	//}

	//ptr, y, data
	if (max == min) min--;

	plot(ptr, x, data, row, max, min);


	return 0;
}
