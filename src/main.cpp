#include "raw10toraw16.h"
#include "calculateExVar.h"
#include "readsony.h"
#include "addnoise.h"
int main(int argc, char** argv)
{
	//std::string iso_file_list = "E:/project/super_night_denoise/list_by_class/all_iso.list";
	//const std::string  iso_parameter = "E:/project/super_night_denoise/list_by_class/all_iso_parameter.txt";
	//getExVarAllIso(iso_file_list, iso_parameter);
	////////////const std::string file_raw = "E:/project/super_night_denoise/test/00001_00_10s.ARW";
	//const std::string file_raw = "IMG_20201210_171248_iso[00100]_exp[00015]_ag[0.000]_p[ZSLSnapshotJpeg]_req[1]_batch[0]_BPS[0]_port[0]_w[4640]_h[3472].RAW";
	//readRaw14(file_raw);


	//const char* file_list = "E:/project/super_night_denoise/list_by_class/iso00100.list";
	//raw10toraw16Files(file_list);

	//const string file_list = "E:/project/super_night_denoise/test/00001_00_10s.ARW";
	//const string dst_file = "E:/project/super_night_denoise/test/00001_00_10s_denoise.ARW";

	const string file_list = "E:/project/super_night_denoise/test/test.raw";
	const string dst_file = "E:/project/super_night_denoise/test/test_denoise.raw";
	int iso = 3200;
	float k = 2.0;
	float sigmaSquare = 10.0;
	generateNoiseSample(file_list, iso, k, sigmaSquare, dst_file);
	return 0;

}
