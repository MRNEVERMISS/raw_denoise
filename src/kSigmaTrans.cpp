#include "kSigmaTrans.h"
#include "util.h"

//	K-sigma±ä»»
int kSigmaTransform(const std::string& raw, int& iso, float& k, float& sigmaSquare, const std::string& dst_path)
{
	vector<float> vec;
	readBinary2vector(vec, raw);

	vector<float> dst;
	for (int i = 0; i < vec.size(); i++ )
	{
		float value = vec[i] / k + sigmaSquare / pow(k, 2);
		dst.push_back(value);
	}

	ofstream outFile(dst_path, ios::out | ios::binary);
	for (int i = 0; i < dst.size(); i++)
	{

		float expectation = dst[i];
		outFile.write((char*)&expectation, sizeof(expectation));

	}
	outFile.close();
	return 0;
}

//	K-sigmaÄæ±ä»»
int kSigmaTransformInvers( const std::string& raw, int& iso, float& k, float& sigmaSquare, const std::string& dst_path )
{
	vector<float> vec;
	readBinary2vector(vec, raw);

	vector<float> dst;
	for (int i = 0; i < vec.size(); i++)
	{
		float value = (pow(k,2)*vec[i]-sigmaSquare)/k;
		dst.push_back(value);
	}

	ofstream outFile(dst_path, ios::out | ios::binary);
	for (int i = 0; i < dst.size(); i++)
	{

		float expectation = dst[i];
		outFile.write((char*)&expectation, sizeof(expectation));

	}
	outFile.close();

	return 0;
}