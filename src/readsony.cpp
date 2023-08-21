#include "readsony.h"

int readRaw14(const std::string& temp)
{
	std::ifstream fin;
	// 
	fin.open(temp, std::ios::binary);
	if (!fin) {
		//std::cerr << "open failed: " << temp << std::endl;
		printf("can not open file");
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

	//short int* buffer = new short int[length];
	//fin.read((char*)buffer, length/2);
	//for (int i = 0; i < length / 2; i++)
	//{
	//	printf("value is %d\n", buffer[i]);
	//}


	while (1)
	{
		;
	}
	return 0;
}
