#ifndef __UTIL_H_
#define  __UTIL_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
short int* readBinary2vector(const std::string& ex_path);
int readBinary2vector(vector<float>& ex, const std::string& ex_path);
int readBinary2vector(short int *dst, const std::string& ex_path);
#endif
