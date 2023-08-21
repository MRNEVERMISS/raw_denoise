#ifndef  __KSIGMATRANS_H_
#define __KSIGMATRANS_H_
#include <iostream>
#include <string>
using namespace std;
int kSigmaTransform(const std::string& raw, int& iso, float& k, float& sigmaSquare, const std::string& dst_path);
int kSigmaTransformInvers(const std::string& raw, int& iso, float& k, float& sigmaSquare, const std::string* dst_path);
#endif