#ifndef __RAW10TORAW16_H__     
#define __RAW10TORAW16_H__       
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





/*
功能：
将单个raw10图像转换为raw16图像
参数:
src		待转换的raw10图像的路径
width	待转换的raw10的宽度(这里默认是5808)
height	待转换的raw10的高度(这里默认是3472)
stride	raw10图像的步长(这里默认是5808)
dst		转换后的raw16的保存路径
*/
int raw10toraw16Single(const char* src, int width, int height, int stride, const char* dst);

/*
功能：将单个raw10图像转换为raw16图像
参数:
file_list	带转换的raw10的文件列表（默认会在同级目录生成对应的raw16的图）
*/
int raw10toraw16Files(const char* file_list);


#endif   