#include "addnoise.h"
#include "util.h"
//#include <stdint.h>

int generateNoiseSample(const std::string& raw, int& iso, float& k, float& sigmaSquare,const std::string& dst_path)
{
	vector<float> raw_vec;
	vector<float> dst_vec;
	short int *indata = NULL;
	indata = readBinary2vector( raw);
	///readBinary2vector(raw_vec, raw);
	//for (int i = 0; i < raw_vec.size(); i++)
	//{
	//	std::cout << raw_vec[i] << std::endl;
	//}
	std::cout << "vector的size是" << raw_vec.size() << std::endl;
	while (indata != NULL )
	{
		short int img_data = *indata;
		float temp = img_data + k*possion(img_data / k) + gaussrand(0, sigmaSquare);
		dst_vec.push_back(temp);
		//printf("合成的噪声是%f\n", temp);
	}
	//for (int i = 0; i < raw_vec.size(); i++)
	//{
	//	printf("raw_vec[i]是%f\n", raw_vec[i]);
	//	float temp = raw_vec[i] + k*possion(raw_vec[i] / k) + gaussrand(0, sigmaSquare);
	//	dst_vec.push_back(temp);
	//	//dst_vec[i] = raw_vec[i]+k*possion(raw_vec[i] / k) + gaussrand(0, sigmaSquare);
	//	printf("合成的噪声是%f\n", dst_vec[i]);
	//}

	ofstream outFile(dst_path, ios::out | ios::binary);
	for (int i = 0; i < dst_vec.size(); i++)
	{

		short int  expectation = dst_vec[i];
		outFile.write((char*)&expectation, sizeof(expectation));

	}
	outFile.close();
	return 0;
}





double gaussrand_NORMAL() {
	static double V1, V2, S;
	static int phase = 0;
	double X;


	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;


			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);


		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);


	phase = 1 - phase;


	return X;
}


/************************************************************************/
/* 
生成期望是mena,标准差是stdc的高斯分布

*/
/************************************************************************/
double gaussrand(double mean, double stdc) {
	return mean + gaussrand_NORMAL() * stdc;
}




//	高德纳已经给出了这个算法
int possion(double Lambda)  /* 产生一个泊松分布的随机数，Lamda为总体平均数*/
{
	////int Lambda = 20, k = 0;
	int k = 0;
	long double p = 1.0;
	long double l = exp(-Lambda);  /* 为了精度，才定义为long double的，exp(-Lambda)是接近0的小数*/
	printf("%.15Lf\n", l);
	while (p >= l)
	{
		double u = U_Random();
		p *= u;
		k++;
	}
	return k - 1;
}

double U_Random()   /* 产生一个0~1之间的随机数 */
{
	double f;
	srand((unsigned)time(NULL));
	f = (float)(rand() % 100);
	/* printf("%fn",f); */
	return f / 100;
}



//double randomUniform(double dMinValue,double dMaxValue)
//{
//	double pRandomValue = (double)(rand() / (double)RAND_MAX);
//	pRandomValue = pRandomValue*(dMaxValue - dMinValue) + dMinValue;
//	return pRandomValue;
//}
//
////	泊松分布
//long randomPossion(double lambda)
//{
//	double x = -1, u;
//	double log1, log2;
//	log1 = 0;
//	log2 = -lambda;
//
//	////	这里的dMin和dMax的值可能需要修改	//	todo
//	double dMin = 0.0;
//	double dMax = 255.0;
//	do
//	{
//		u = randomUniform(dMin,dMax);
//		log1 += log(u);
//		x++;
//	} while (log1 >= log2);
//	return x;
//}