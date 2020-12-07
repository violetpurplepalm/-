#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#include <string>
#include <cmath>
void print(vector<double>& v) {
        for (auto c : v) {
                cout << c << " ";
        }
        cout << endl;
}
 
void rgb_to_xyz(vector<double>rgb) {  
        vector<double>xyz = {0,0,0};
 
        for (int i = 0; i < 3; ++i) {
                rgb[i] = (rgb[i] / 255);
                if (rgb[i] > 0.04045) { rgb[i] = pow(((rgb[i] + 0.055) / 1.055), 2.4); }
                else { rgb[i] = rgb[i] / 12.92; }
                rgb[i] *= 100;
        }
        xyz[0] = rgb[0] * 0.4124 + rgb[1] * 0.3576 + rgb[2] * 0.1805;
        xyz[1] = rgb[0] * 0.2126 + rgb[1] * 0.7152 + rgb[2] * 0.0722;
        xyz[2] = rgb[0] * 0.0193 + rgb[1] * 0.1192 + rgb[2] * 0.9505;
        cout << "XYZ" << ": ";
        print(xyz);
}
vector<double> cmy_to_rgb(vector<double>cmy){  
        vector<double> rgb = { 0,0,0 };
        for (int i = 0; i < 3; ++i) {
                rgb[i] = (1 - cmy[i]) * 255;
        }
                cout << "RGB" << ": ";
                print(rgb);
                return rgb;
       
}
void cmy_to_cmyk(vector<double>cmy){  
        vector<double> cmyk = { 0,0,0,1 };
        double k=1;
        k = min(min(cmy[0], cmy[1]), cmy[2]);
        if (k != 1) {
                for (int i = 0; i < 3; ++i) {
                        cmyk[i] = (cmy[i] - k)/(1-k);
 
                }
        }
        cmyk[3] = k;
        cout << "CMYK" << ": ";
        print(cmyk);
       
 
}
vector<double> cmyk_to_cmy(vector<double>cmyk){
        vector<double> cmy = { 0,0,0 };
        for (int i = 0; i < 3; ++i) {
                cmy[i] = cmyk[i] * (1 - cmyk[3]) + cmyk[3];
        }
        cout << "CMY" << ": ";
        print(cmy);
        return cmy;
}
vector<double> rgb_to_cmy(vector<double>rgb){
        vector<double> cmy = { 0,0,0 };
        for (int i = 0; i < 3; ++i) {
                cmy[i] = 1 - (rgb[i] / 255);
        }
        cout << "CMY" << ": ";
        print(cmy);
        return cmy;
       
}
 
vector<double> hsl_to_hsv(vector<double>hsl){
        vector<double> hsv(3);
        hsl[0] = hsl[0]*360;
        double min;
        hsv[0] = hsl[0];
        min = hsl[2];
        if ((1 - hsl[2]) < min) { min = 1 - hsl[2]; }
        hsv[2] = hsl[2] + hsl[1] * min;
        if (hsv[2] == 0) { hsv[1] = 0; }
        else {hsv[1] =  2 * (1 - (hsl[2] / hsv[2])); }
        hsv[0] = hsv[0]/360;
        cout << "HSV" << ": ";
        print(hsv);
        return(hsv);
 
}
 
void hsv_to_hsl(vector<double>hsv){
        vector <double> hsl(3);
        double min;
        hsv[0] *= 360;
        hsl[0] = hsv[0];
        hsl[2] = hsv[2] * (1 - (hsv[1] / 2));
        min = hsl[2];
        if ((1 - hsl[2]) < min) { min = 1 - hsl[2]; }
        if (hsl[2] == 0 || hsl[2] == 1) { hsl[1] = 0; }
        else hsl[1] = (hsv[2] - hsl[2]) / min;
        hsl[0] /= 360;
        cout << "HSL" << ": ";
        print(hsl);
}
vector<double> rgb_to_hsv(vector<double> rgb) {
        double MAX, MIN, DELTA;
        vector<double>hsv(3);
        rgb[0] = rgb[0] / 255;
        rgb[1] = rgb[1] / 255;
        rgb[2] = rgb[2] / 255;
        MAX = max(max(rgb[0], rgb[1]), rgb[2]);
        MIN = min(min(rgb[0], rgb[1]), rgb[2]);
        DELTA = MAX - MIN;
        if (MAX == 0) hsv[1] = 0;
        else {
                hsv[1] = (MAX - MIN) / MAX;
                hsv[2] = MAX;
        }
        if (DELTA == 0) hsv[0] = 0;
        else {
                if (MAX == rgb[0]) hsv[0] = 60 * ((rgb[1] - rgb[2]) / DELTA);
                else if (MAX == rgb[1]) hsv[0] = 60 * ((rgb[2] - rgb[0]) / DELTA + 2);
                else if (MAX == rgb[2]) { hsv[0] = 60 * ((rgb[0] - rgb[1]) / DELTA + 4); }
                if (hsv[0] < 0) { hsv[0] = hsv[0] + 360; }
        }
        hsv[0] /= 360;
       
        cout << "HSV" << ": ";
        print(hsv);
        return(hsv);
 
}
 
vector<double> hsv_to_rgb(vector<double>hsv) {
        vector<double> rgb(3);
        double var_i, var_r, var_1, var_2, var_3, var_h, var_g, var_b;
        if (hsv[1] == 0)
        {
                rgb[0] = hsv[2] * 255;
                rgb[1] = hsv[2] * 255;
                rgb[2] = hsv[2] * 255;
        }
        else
        {
                var_h = hsv[0] * 6;
                if (var_h == 6) var_h = 0;    //H must be < 1
                var_i = int(var_h);        //Or ... var_i = floor( var_h )
                var_1 = hsv[2] * (1 - hsv[1]);
                var_2 = hsv[2] * (1 - hsv[1] * (var_h - var_i));
                var_3 = hsv[2] * (1 - hsv[1] * (1 - (var_h - var_i)));
 
                if (var_i == 0) { var_r = hsv[2]; var_g = var_3; var_b = var_1; }
                else if (var_i == 1) { var_r = var_2; var_g = hsv[2]; var_b = var_1; }
                else if (var_i == 2) { var_r = var_1; var_g = hsv[2]; var_b = var_3; }
                else if (var_i == 3) { var_r = var_1; var_g = var_2; var_b = hsv[2]; }
                else if (var_i == 4) { var_r = var_3; var_g = var_1; var_b = hsv[2]; }
                else { var_r = hsv[2]; var_g = var_1; var_b = var_2; }
 
                rgb[0] = var_r * 255;
                rgb[1] = var_g * 255;
                rgb[2] = var_b * 255;
        }
        cout << "RGB" << ": ";
        print(rgb);
        return rgb;
}
int main()
{
        vector<double> koord, new3sys(3), new4sys(4);
        string start;
        double c;
 
        cout << "Enter the source system" << endl;
        cin >> start;
        cout << "Enter color coordinates separated by space" << endl;
        for (int i = 0; i < start.size(); ++i) {
                cin >> c;
                koord.push_back(c);
        }
       
        if (start == "RGB" ) {
                rgb_to_xyz(koord);
                new3sys = rgb_to_cmy(koord);
                cmy_to_cmyk(new3sys);
                new3sys = rgb_to_hsv(koord);
                hsv_to_hsl(new3sys);
        }
        else if (start=="HSL"){
                koord = hsl_to_hsv(koord);
                koord = hsv_to_rgb(koord);
                rgb_to_xyz(koord);
                koord = rgb_to_cmy(koord);
                cmy_to_cmyk(koord);
        }
        else if (start == "HSV") {
                hsv_to_hsl(koord);
                koord = hsv_to_rgb(koord);
                rgb_to_xyz(koord);
                koord = rgb_to_cmy(koord);
                cmy_to_cmyk(koord);
        }
        else if (start == "CMY") {
                cmy_to_cmyk(koord);
                koord = cmy_to_rgb(koord);
                rgb_to_xyz(koord);
                koord = rgb_to_hsv(koord);
                hsv_to_hsl(koord);
        }
        else if (start == "CMYK") {
                new3sys = cmyk_to_cmy(koord);
                new3sys = cmy_to_rgb(new3sys);
                rgb_to_xyz(new3sys);
                new3sys = rgb_to_hsv(new3sys);
                hsv_to_hsl(new3sys);
        }
        return 0;
 
}
