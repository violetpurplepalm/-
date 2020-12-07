#include "tgaimage.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void brez(int x0, int y0, int x1, int y1, TGAImage & image)
{
	int A, B, sign;
	A = y1 - y0;
	B = x0 - x1;
	if (abs(A) > abs(B)) sign = 1;
	else sign = -1;
	int signa, signb;
	if (A < 0) signa = -1;
	else signa = 1;
	if (B < 0) signb = -1;
	else signb = 1;
	int f = 0;
	image.set(x0, y0, red);
	int x = x0, y = y0;
	if (sign == -1)
	{
		do {
			f += A * signa;
			if (f > 0)
			{
				f -= B * signb;
				y += signa;
			}
			x -= signb;
			image.set(x, y, red);
			

		} while (x != x1 || y != y1);
	}
	else
	{
		do {
			f += B * signb;
			if (f > 0) {
				f -= A * signa;
				x -= signb;
			}
			y += signa;
			image.set(x, y, red);
		} while (x != x1 || y != y1);
	}
}

vector<vector<int>> prll_transl(vector<vector<int>>&v) {
	vector<int>transfer = { 400,100, 50};// сдвиг на вектор transfer
	for (int i = 0; i <= 3; ++i) {
		v[i][0] = v[i][0] + transfer[0];
		v[i][1] = v[i][1] + transfer[1];
		v[i][2] = v[i][2] + transfer[2];
	}
	return v;
};

vector<vector<int>> scaling(vector<vector<int>>& v) {
	vector<double>S = {0.7,0.6,0.4 };// масштабирование ;
	for (int i = 0; i <= 3; ++i) {             
		v[i][0] = v[i][0]*S[0];
		v[i][1] = v[i][1]*S[1];
		v[i][1] = v[i][2]*S[2];
	}
	return v;
};
#define pi 3.14159265
vector<vector<int>> turn(vector<vector<int>>& v) {
	vector<double> Q = { pi / 5, pi/8, pi/9 };// поворот на угол Q[0], Q[1], Q[2], оси Х, Y, Z соответственно;
	int x, y,z;
	double a = Q[0],
		   b = Q[1],
		   c = Q[2];
	for (int i = 0; i <= 3; ++i) {    
		x = v[i][0];
		y = v[i][1];
		z = v[i][2];
		v[i][0] = x*cos(b)*cos(c) - y*sin(c)*cos(b)+z*sin(b);
		v[i][1] = x * (sin(a) * sin(b) * cos(c) + cos(a) * sin(c)) - y * (sin(a) * sin(b) * sin(c) - cos(a) * cos(c)) - z * (sin(a) * cos(b));
		v[i][2] = -x * (sin(b) * cos(a) * cos(c) - sin(a) * sin(c)) + y * (sin(c) * sin(b) * cos(a) + cos(c) * sin(a)) + z * (cos(a) * cos(b));
		
	}
	return v;
};
void draw(vector<vector<int>>& v, TGAImage& image) {
	brez(v[0][0], v[0][1], v[1][0], v[1][1], image);
	brez(v[0][0], v[0][1], v[2][0], v[2][1], image);
	brez(v[2][0], v[2][1], v[1][0], v[1][1], image);
	brez(v[2][0], v[2][1], v[3][0], v[3][1], image);
	brez(v[0][0], v[0][1], v[3][0], v[3][1], image);
	brez(v[1][0], v[1][1], v[3][0], v[3][1], image);
}


int main(int argc, char** argv) {
	TGAImage image(1000, 1000, TGAImage::RGB);
	
	vector<vector<int>> triangle = { {700,350,200},{500,600,300},{850,550,200},{500,500,500} }; //пусть дана произвольная треугольная пирамида
	draw(triangle, image);
	triangle = prll_transl(triangle);
	triangle = scaling(triangle);
	triangle = turn(triangle);
	draw(triangle, image);
	image.set(100, 100, red);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	
	return 0;
}
