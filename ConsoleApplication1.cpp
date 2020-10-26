#include "tgaimage.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <cmath>
#include <vector>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
void brez(double x0, double y0, double x1, double y1, TGAImage& image) {
	double d, dx, dy, x, y, ox1, ox2, oy1, oy2, fx = 1, fy = 1;
	if ((x0 >= x1) and (y0 >= y1)) {
		swap(x0, x1);
		swap(y0, y1);
	}
	oy1 = min(y0, y1); 
	oy2 = max(y0, y1);
	ox1 = min(x0, x1);
	ox2 = max(x0, x1);
	if (x0 > x1) { 
		ox1 = x1;
		oy2 = y1;
		fx = -1;
	}
	else if (y0 > y1) {
		ox2 = x1;
		oy1 = y1;
		fy = -1;
	}
	dy = abs(y1 - y0);
	dx = abs(x1 - x0);
	d = 2 * dy - dx;
	x = x0;
	y = y0;
	if (abs(dx) > abs(dy)) {
		do {
			image.set(round(x), round(y), red);
			if (d < 0) { d += 2 * dy; }
			else {
				d += 2 * (dy - dx);
				y = y + fy;
			}
			x = x + fx;
		} while (x <= ox2 and x >= ox1 and y <= oy2 and y >= oy1);
	}
	else {
		do {
			image.set(round(x), round(y), red);
			if (d < 0) { d += 2 * dx; }
			else {
				d += 2 * (dx - dy);
				x = x + fx;
			}
			y = y + fy;
		} while (x <= ox2 and x >= ox1 and y <= oy2 and y >= oy1);
	}
}
void drawObj1(TGAImage& image)
{
	ifstream fin("african_head.obj"); // obj-файл должен быть в папке с решением
	char ch;
	string str;
	vector<vector<double>> points; 
	while (fin >> str) {
		
		if (str == "f") {
			int f1, f2, f3, pass;
			char ch;
			fin >>
				f1 >> ch >> pass >> ch >> pass >>f2 >> ch >> pass >> ch >> pass >> f3 >> ch >> pass >> ch >> pass;
			f1--; // вычитаем 1 т.к вершины в векторе нумеруются с нуля
			f2--;
			f3--;
			brez(points[f1][0]+ 1500, points[f1][1]+ 1500, points[f2][0]+ 1500, points[f2][1]+1500, image); //строим треугольник из трех отрезков, переход в систему координат 
			brez(points[f2][0] + 1500, points[f2][1] + 1500, points[f3][0] + 1500, points[f3][1] + 1500, image);    //с центром изображения в точке (1500, 1500, 1500)
			brez(points[f1][0] + 1500, points[f1][1] + 1500, points[f3][0] + 1500, points[f3][1] + 1500, image);
		}
		if (str == "v") {
			float f1, f2, f3;
			fin >> f1 >> f2 >> f3;
			f1 *= 1000; 
			f2 *= 1000;
			f3 += 1000;   //теперь значения координат вершин в отрезке между -1000 и 1000
			points.push_back({ f1,f2,f3 }); //добавляем в вектор координаты вершины
		}
	}
	cout << points.size();
	fin.close();
}
int main(int argc, char** argv) {
	
	TGAImage image(3000, 3000, TGAImage::RGB);
	drawObj1(image);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	return 0;
}