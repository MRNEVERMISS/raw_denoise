#include "raw10toraw16.h"

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
int raw10toraw16Single(const char* src, int width, int height, int stride, const char* dst)
{
	FILE *fp = fopen(src, "rb");

	if (!fp)
	{
		printf("Fail to open file %s\n", src);
		return -1111;
	}
	FILE *fo = fopen(dst, "wb");
	if (!fo)
	{
		printf("Fail to open file %s\n", dst);
		fclose(fp);
		return -1;
	}
	unsigned char buf[1024 * 8];
	int i = 0;
	int j = 0;
	int n = 0;
	while (!feof(fp))
	{
		for (n = 0; n < height; n++)
		{
			int ret = fread(buf, 1, stride, fp);
			if (!ret)
			{
				break;
			}
			for (j = 0; j < width / 4; j++)
			{
				unsigned char *p = buf + j * 5;
				for (i = 0; i < 4; i++)
				{
					unsigned short d = p[i];

					printf("value is %d\n", d);
					d = d << 2;
					d = d | ((p[4] >> (i * 2)) & 0x3);
					fwrite(&d, 2, 1, fo);
				}
			}
		}
	}
	fclose(fo);
	fclose(fp);
	return 0;
}
/*
功能：将单个raw10图像转换为raw16图像
参数:
file_list	带转换的raw10的文件列表（默认会在同级目录生成对应的raw16的图）
*/
int raw10toraw16Files(const char* file_list)
{
	//	读取文件list

	string file_list_temp = file_list;
	ifstream in(file_list_temp);
	string s;
	string dst_temp;
	int width = 5808;
	int height = 3472;
	int stride = 5808;
	while (getline(in, s))//逐行读取数据并存于s中，直至数据全部读取
	{
		cout << s << endl;
		dst_temp = s + "_unpack.RAW";
		raw10toraw16Single(s.c_str(), width, height, stride, dst_temp.c_str());
	}
	in.close();
	return 0;
}
/********************************** END **********************************************/