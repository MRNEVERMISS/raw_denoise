#include "calculateExVar.h"
#include "fitlines.h"

int computeExVarFromRaw10(const std::string& raw_list, const std::string& Ex_path, const std::string& Var_path)
{

	//vector<float> Ex;
	//vector<float> Var;
	vector<float> Ex;
	vector<float> Var;
	ifstream myfile(raw_list);
	std::string gray_path;

	vector<cv::Mat> matbox;
	string temp;
	if (!myfile.is_open())
	{
		cout << "未成功打开文件" << endl;
	}
	while (getline(myfile, temp))
	{

		std::ifstream fin;
		// 
		fin.open(temp, std::ios::binary);
		if (!fin) {
			std::cerr << "open failed: " << temp << std::endl;
		}
		// 
		fin.seekg(0, fin.end);
		// 
		int length = fin.tellg();
		// 
		fin.seekg(0, fin.beg);
		std::cout << "file length: " << length << std::endl;

		// load buffer
		char* buffer = new char[length];

		fin.read(buffer, length);


		//for (int h = 0; h < length; h++)
		//{
		//	//std::cout << "原始值是" << std::endl;
		//	//std::cout << buffer[h] << std::endl;
		//	printf("原始值是%d\n", buffer[h]);
		//}

		//	将16bit的unpacked raw读入进来
		cv::Mat image(cv::Size(5808, 3472), CV_8SC1, buffer);
		cv::Mat srcImage = image(Rect(1783, 883, 1511, 125));		//	将grayscale chart区域作为roi提取出来
		matbox.push_back(srcImage);
		//imageLuminance(file_path, gray_path);
	}

	ofstream fout;
	fout.open("fuckfuck.txt", std::ios::app);

	uchar* qq;
	for (int k = 0; k < matbox.size(); k++)
	{
		cv::Mat temp_mat = matbox[k];
		for (int i = 0; i < matbox[0].rows; i++)
		{

			qq = temp_mat.ptr<uchar>(i);
			for (int j = 0 * matbox[0].cols / 20; j < 1 * matbox[0].cols / 20; j++)
			{
				int value = qq[j];
				fout << value << endl;
			}
			//int value = buffer[i];

			//printf("%d ", buffer[i]);
		}
	}


	fout.close();




	int row = matbox[0].rows;
	int col = matbox[0].cols;

	uchar *p;
	//vector<float> vec;
	//vector<float> vec4var;
	vector <vector<float> > mean_box;
	vector <vector<float> > var_box;
	//	20个相同亮度块
	for (int k = 0; k < matbox.size(); k++)
	{




		//float sum = 0.0;
		//float var = 0.0;	//	求方差
		vector<float> vec;
		vector<float> vec_var_temp;
		//for (int h = 0; h <= 19; h++ )
		for (int h = 5; h <= 15; h++)
		{

			////	灰阶图去掉头和尾
			//if (h <= 4 || h >= 15)
			//{
			//	continue;
			//}

			float sum = 0.0;
			float var_temp = 0.0;
			for (int j = (col*h / 20); j < (col*(h + 1)) / 20; ++j)
			{
				for (int i = 0; i < row; i++)
				{
					float value = 0.0;
					p = matbox[k].ptr<uchar>(i);
					if (i % 2 == 0)
					{
						if (j % 2 == 0)
						{
							value = p[j];
							sum += value;
						}


					}
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
						{
							value = p[j];
							sum += value;
						}
					}


					//sum /= matbox.size()*1.0;
					//vec.push_back(sum);

				}

			}
			int chushu = (col / 20)*row;
			sum /= chushu;
			vec.push_back(sum);



			for (int j = (col*h / 20); j < (col*(h + 1)) / 20; ++j)
			{
				for (int i = 0; i < row; i++)
				{
					//	RGB通道分开来取，这里先去G通道

					p = matbox[k].ptr<uchar>(i);
					float value = 0.0;

					if (i % 2 == 0)
					{
						if (j % 2 == 0)
						{
							value = p[j];
							sum += value;
						}


					}
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
						{
							value = p[j];
							sum += value;
						}
					}

					//float value = p[j];
					var_temp += pow(value - sum, 2);

					//sum /= matbox.size()*1.0;
					//vec.push_back(sum);

				}

			}
			var_temp /= chushu;
			vec_var_temp.push_back(var_temp);
			sum = 0.0;
			var_temp = 0.0;


		}
		mean_box.push_back(vec);
		var_box.push_back(vec_var_temp);
		vec.clear();
		vec_var_temp.clear();
	}



	ofstream fout_file;
	fout_file.open("mean_value.txt", std::ios::app);
	std::cout << "mean_box的size" << mean_box[0].size() << "  " << mean_box.size() << std::endl;
	//for (int j = 0; j < mean_box[0].size(); j++)
	//{
	//	//mean = 0.0;
	//	//variance = 0.0;
	//	for (int i = 0; i < mean_box.size(); i++)
	//	{
	//		// for (int j = 0;)
	//		float mean = mean_box[i][j];
	//		fout_file << mean << endl;
	//		/*mean = mean_box[i][j];*/
	//	}
	//}


	fout_file.close();







	//	通过mean_box 求方差和期望
	float mean = 0.0;
	float variance = 0.0;
	for (int j = 0; j < mean_box[0].size(); j++)
	{
		mean = 0.0;
		variance = 0.0;
		for (int i = 0; i < mean_box.size(); i++)
		{
			// for (int j = 0;)
			mean += mean_box[i][j];
			/*mean = mean_box[i][j];*/
		}
		mean /= mean_box.size();

		//for (int i = 0; i < var_box.size(); i++)
		//{
		//	// for (int j = 0;)
		//	variance += (var_box[i][j]);
		//	////float value = mean_box[i][j];
		//	///variance += pow(value - mean, 2);
		//}
		//variance /= var_box.size();
		////variance = sqrt(variance);

		//Var.push_back(variance);
		Ex.push_back(mean);
		mean = 0.0;
		variance = 0.0;
	}


	std::cout << "EX的大小是" << Ex.size() << std::endl;


	float var_tmp = 0.0;


	//for (int h = 0; h <= 19; h++)
	for (int h = 0; h <= 10; h++)
	{
		////	灰阶图去掉头和尾
		//if (h <= 4 || h >= 15)
		//{
		//	continue;
		//}

		float var_temp = 0.0;
		for (int k = 0; k < matbox.size(); k++)
		{

			//float sum = 0.0;

			for (int j = (col*h / 20); j < (col*(h + 1)) / 20; ++j)
			{
				for (int i = 0; i < row; i++)
				{
					float value = 0.0;
					p = matbox[k].ptr<uchar>(i);

					if (i % 2 == 0)
					{
						if (j % 2 == 0)
						{
							value = p[j];
							//sum += value;
							var_tmp += pow(value - Ex[h], 2);
						}


					}
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
						{
							value = p[j];
							//sum += value;
							var_tmp += pow(value - Ex[h], 2);
						}
					}

					//float value = p[j];

				}

			}

		}
		var_tmp /= (matbox.size() * 20 * row);
		Var.push_back(var_tmp);


	}









	ofstream outFile(Ex_path, ios::out | ios::binary);
	for (int i = 0; i < Ex.size(); i++)
	{

		float expectation = Ex[i];
		outFile.write((char*)&expectation, sizeof(expectation));

	}
	outFile.close();


	ofstream outFileVar(Var_path, ios::out | ios::binary);
	for (int i = 0; i < Var.size(); i++)
	{

		float expectation = Var[i];
		outFileVar.write((char*)&expectation, sizeof(expectation));
	}
	outFileVar.close();

	//while (1)
	//{
	//	;
	//}

	return 0;
}

// E:/project/super_night_denoise/list_by_class/下的文件按照iso分开形成的文件列表
/************************************************************************/
/* 
E:/project/super_night_denoise/list_by_class/iso00100.list
E:/project/super_night_denoise/list_by_class/iso00288.list
E:/project/super_night_denoise/list_by_class/iso00475.list
E:/project/super_night_denoise/list_by_class/iso00850.list
E:/project/super_night_denoise/list_by_class/iso01200.list
E:/project/super_night_denoise/list_by_class/iso01600.list
E:/project/super_night_denoise/list_by_class/iso02400.list
E:/project/super_night_denoise/list_by_class/iso03200.list
E:/project/super_night_denoise/list_by_class/iso04000.list
E:/project/super_night_denoise/list_by_class/iso04800.list
E:/project/super_night_denoise/list_by_class/iso05600.list
E:/project/super_night_denoise/list_by_class/iso06400.list
E:/project/super_night_denoise/list_by_class/iso12800.list                                                                     */
/************************************************************************/
int getExVarAllIso(const std::string& iso_file_list, const std::string& iso_parameter )
{
	ifstream myfile(iso_file_list);
	if (!myfile.is_open())
	{
		cout << "未成功打开文件" << endl;
		return 1;
	}

	ofstream fout;
	fout.open(iso_parameter, std::ios::app);
	fout << "ISO" << " " << "K" << " " << "sigma square" << std::endl;
	string file_list;
	while (getline(myfile, file_list))
	{
		string ex_path = file_list + "_ex.dat";
		string var_path = file_list + "_var.dat";
		float k = 0.0;
		float sigmaSquare = 0.0;
		computeExVarFromRaw10(file_list, ex_path, var_path);
		polyfit(ex_path, var_path, k, sigmaSquare);
		string iso = file_list.substr(0, file_list.rfind("."));
		/*std::cout << "K" << k << "sigma square" << sigmaSquare << std::endl;*/
		fout << iso << " "<<k<<" " << sigmaSquare << std::endl;
	}
	myfile.close();
	fout.close();
}