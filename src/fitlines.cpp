#include "fitlines.h"
#include "util.h"

//	����ex��var��·��
int polyfit(std::string& ex_path, std::string& var_path, float& k, float& sigmaSquare )
{
	//ifstream myfile(ex_path);
	//if (!myfile.is_open())
	//{
	//	cout << "δ�ɹ����ļ�" << endl;
	//	return 1;
	//}
	vector<float> ex;
	readBinary2vector(ex, ex_path);

	vector<float> var;
	readBinary2vector(var, var_path);
	
	//	ͨ����С���˷����y = ax+b
	double ex_mean = 0.0;
	for (int i = 0; i < ex.size(); i++)
	{
		ex_mean += ex[i];
	}
	ex_mean /= ex.size();

	//	ͨ����С���˷����y = ax+b
	double var_mean = 0.0;
	for (int i = 0; i < var.size(); i++)
	{
		var_mean += var[i];
	}
	var_mean /= var.size();

	double fenzi = 0.0;
	for ( int i = 0; i < ex.size(); i++ )
	{
		fenzi += (ex[i] - ex_mean)*(var[i] - var_mean);
	}

	double fenmu = 0.0;
	for (int i = 0; i < ex.size(); i++)
	{
		fenmu += (ex[i] - ex_mean)*(ex[i] - ex_mean);
		printf(" fen mu shi %f\n", fenmu);
	}
	
	if (fenmu > 0.001 )
	{
		k = fenzi / fenmu;
		sigmaSquare = var_mean - k*ex_mean;
	}
	else
	{
		k = 0.0;
		sigmaSquare = 0.0;
	}
	
	return 0;
}


