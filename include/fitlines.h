#ifndef __FITLINES_H__     
#define __FITLINES_H__   
#include <iostream>
#include <fstream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
using namespace cv;


//	读入ex和var的路径
int polyfit(std::string& ex_path, std::string& var_path, float& k, float& sigmaSquare);
//int readBinary2vector(vector<float>& ex, const std::string& ex_path);
#endif   