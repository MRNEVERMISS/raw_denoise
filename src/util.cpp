#include "util.h"
///int readBinary2vector(vector<float>& ex, const std::string& ex_path)
short int* readBinary2vector(const std::string& ex_path)
{
	//vector<double> ex;



	std::ifstream fin;
	// 
	fin.open(ex_path, std::ios::binary);
	if (!fin) {
		std::cerr << "open failed: " << ex_path << std::endl;
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
	short int* ptr = (short int*)buffer;
	//while ( ptr != NULL )
	//{
	//	printf("读入的数值是%d\n", *ptr);
	//	ptr = ptr + 1;
	//}
	///////////////dst = ptr;
	//for (int i = 0; i < length; i++)
	//{
	//	ex.push_back(buffer[i]);
	//}
	fin.close();
	return ptr;
	///return 0;
}

int readBinary2vector(vector<float>& ex, const std::string& ex_path)
{

	//vector<double> ex;



	std::ifstream fin;
	// 
	fin.open(ex_path, std::ios::binary);
	if (!fin) {
		std::cerr << "open failed: " << ex_path << std::endl;
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
	short int* ptr = (short int*)buffer;
	//while ( ptr != NULL )
	//{
	//	printf("读入的数值是%d\n", *ptr);
	//	ptr = ptr + 1;
	//}
	///dst = ptr;
	for (int i = 0; i < length; i++)
	{
		ex.push_back(buffer[i]);
	}
	fin.close();
	return 0;
}