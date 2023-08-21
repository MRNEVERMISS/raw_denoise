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
���ܣ�
������raw10ͼ��ת��Ϊraw16ͼ��
����:
src		��ת����raw10ͼ���·��
width	��ת����raw10�Ŀ��(����Ĭ����5808)
height	��ת����raw10�ĸ߶�(����Ĭ����3472)
stride	raw10ͼ��Ĳ���(����Ĭ����5808)
dst		ת�����raw16�ı���·��
*/
int raw10toraw16Single(const char* src, int width, int height, int stride, const char* dst);

/*
���ܣ�������raw10ͼ��ת��Ϊraw16ͼ��
����:
file_list	��ת����raw10���ļ��б�Ĭ�ϻ���ͬ��Ŀ¼���ɶ�Ӧ��raw16��ͼ��
*/
int raw10toraw16Files(const char* file_list);


#endif   