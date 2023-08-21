#ifndef __ADDNOISE_H__     
#define __ADDNOISE_H__   
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

/*
将单个raw图加上噪声生成带噪声的raw图
*/
int generateNoiseSample(const std::string& raw, int& iso, float& k, float& sigmaSquare, const std::string& dst_path);
//int generateNoiseSample( const std::string& raw, int& iso, float& k, float& sigmaSquare );
double gaussrand_NORMAL();
double gaussrand(double mean, double stdc);
double U_Random();
int possion(double Lambda);
//double randomUniform(double dMinValue, double dMaxValue);
//long randomPossion(double lambda);


#endif