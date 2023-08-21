#include "raw10toraw16.h"

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
���ܣ�������raw10ͼ��ת��Ϊraw16ͼ��
����:
file_list	��ת����raw10���ļ��б�Ĭ�ϻ���ͬ��Ŀ¼���ɶ�Ӧ��raw16��ͼ��
*/
int raw10toraw16Files(const char* file_list)
{
	//	��ȡ�ļ�list

	string file_list_temp = file_list;
	ifstream in(file_list_temp);
	string s;
	string dst_temp;
	int width = 5808;
	int height = 3472;
	int stride = 5808;
	while (getline(in, s))//���ж�ȡ���ݲ�����s�У�ֱ������ȫ����ȡ
	{
		cout << s << endl;
		dst_temp = s + "_unpack.RAW";
		raw10toraw16Single(s.c_str(), width, height, stride, dst_temp.c_str());
	}
	in.close();
	return 0;
}
/********************************** END **********************************************/