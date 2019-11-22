#include <opencv2\opencv.hpp>
#include <cstdio>
#include <cstring>
using namespace cv;

void encode(std::string input_file_name, std::string mask_file_name, std::string out_file_name, int channel = 1) {
	
	Mat src = imread(input_file_name);
	Mat mask = imread(mask_file_name);
	for (int r = 0; r < src.rows; r++) {
		for (int c = 0; c < src.cols; c++) {
			Vec3b back = src.at<Vec3b>(r, c); // b g r 
			back[channel] = mask.at<Vec3b>(r, c)[0] ? (back[channel] | 0x1) : (back[channel] & 0xfe);
			src.at<Vec3b>(r, c) = back;
		}
	}
	imwrite(out_file_name, src);
}

void decode(std::string secret_file_name, std::string mask_file_name, int channel = 1) {
	// chanel: b g r 
	Mat secret = imread(secret_file_name);
	Mat mask(secret.size(), CV_8UC3, Scalar(0, 0, 0));
	int src_w = secret.cols, src_h = secret.rows;
	for (int r = 0; r < src_h; r++) {
		for (int c = 0; c < src_w; c++) {
			Vec3b back = secret.at<Vec3b>(r, c); // b g r 
			uchar hh = back[channel] & 1;
			hh *= 255;
			mask.at<Vec3b>(r, c) = Vec3b(hh, hh, hh);
		}
	}
	imwrite(mask_file_name, mask);
}


int main(int argc, char *argv[]) {

	const int channel = 1; // low bit of green channle saves mask infomation
	
	/*
	-e sdu.bmp mask.bmp hiddenInfo.png 
	-d hiddenInfo.png infoMask.png
	*/
	std::string input_file_name;
	std::string mask_file_name;
	std::string out_file_name;
	std::string decode_mask_file_name;

	if (argc == 5 && !strcmp(argv[1], "-e")) {
		input_file_name.append(argv[2]);
		mask_file_name.append(argv[3]);
		out_file_name.append(argv[4]);
		encode(input_file_name, mask_file_name, out_file_name, channel);
		printf("encryption done!");

	}
	else if (argc == 4 && !strcmp(argv[1], "-d")) {
		out_file_name.append(argv[2]);
		decode_mask_file_name.append(argv[3]);
		decode(out_file_name, decode_mask_file_name, channel);
		printf("decryption done!");
	}
	else {
		printf("run command:\n\n");
		printf("WARNING: ${} can be repalced, but file type don't change.\n\n");
		printf("encrpt: \n\t-e ${input_file_name}.bmp ${mask_file_name}.bmp ${output_file_name}.png\n");
		puts("\n");
		printf("decrypt: \n\t-d ${secret_file_name}.png ${mask_file_name}.png\n");
	}

	return 0;
}