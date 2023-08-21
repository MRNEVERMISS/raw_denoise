#ifndef __CALCULATEEXVAR_H__     
#define __CALCULATEEXVAR_H__   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
using namespace std;
using namespace cv;



int computeExVarFromRaw10(const std::string& raw_list, const std::string& Ex_path, const std::string& Var_path);
int getExVarAllIso(const std::string& iso_file_list, const std::string& iso_parameter);

#endif   