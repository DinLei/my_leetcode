//
// Created by 丁磊 on 2019/9/17.
//

#include <stdio.h>
#include <fstream>
#include "bitmap.h"
#include "AdUtil.h"
#include "../interfaces/Util.h"

Bitmap::Bitmap(const char* gds_file) {
	bm_size = (BIT_CAPACITY >> 3) + 1;
	bitmap = (unsigned char*)malloc(bm_size);
	gds_file_str = gds_file;

	REGIST_HANDLER(gds_file_str);
	Update();
}

Bitmap::~Bitmap() {
	UNREGIST_HANDLER(gds_file_str);
	free(bitmap);
	bitmap = NULL;
}

void normalize(std::string& input) {
	input = AdUtil::Trim(input);
	AdUtil::StringTolower(input);
}

void Bitmap::set_1(const char* keys, const char* delim) {
	vector<std::string> gds;
	AdUtil::Split2(gds, keys, delim);
	for (vector<std::string>::iterator it = gds.begin(); it != gds.end(); it++) {
		std::string input = *it;
		normalize(input);
		size_t the_hash_val = xhash_str(input);
		size_t row = the_hash_val >> 3;
		if (row < bm_size)
			bitmap[row] |= (1 << (the_hash_val & 7));
	}
}

void Bitmap::set_0(const char* keys, const char* delim) {
	vector<std::string> gds;
	AdUtil::Split2(gds, keys, delim);
	for (vector<std::string>::iterator it = gds.begin(); it != gds.end(); it++) {
		std::string input = *it;
		normalize(input);
		//    size_t the_hash_val = AdUtil::hash(*it);
		size_t the_hash_val = xhash_str(input);
		size_t row = the_hash_val >> 3;
		if (row < bm_size)
			bitmap[row] &= ~(1 << (the_hash_val & 7));
	}
}

char* Bitmap::get(const char* keys, const char* delim) {
	vector<std::string> gds;
	AdUtil::Split2(gds, keys, delim);
	std::string result = "";
	int i = 0;
	for (vector<std::string>::iterator it = gds.begin(); it != gds.end(); it++) {
		std::string input = *it;
		normalize(input);
		size_t the_hash_val = xhash_str(input);
		size_t row = the_hash_val >> 3;
		if (row > bm_size) {
			result += "-1";
		}
		else {
			int the_bit_val = (bitmap[row] >> (the_hash_val & 7)) & 1;
			result += AdUtil::int_to_str(the_bit_val);
		}
		if (i < gds.size() - 1) {
			result += delim;
			i++;
		}
	}
	char* buf = (char*)malloc(result.size());
	strcpy(buf, result.c_str());
	return buf;
}

bool Bitmap::Update() {
	ifstream infile;
	int batch_num = 500, counter = 1;
	std::string one_input;
	vector<std::string> batch_inputs;
	infile.open(gds_file_str.c_str(), std::ios::in);
	if (!infile) return false;

	memset(bitmap, 255, bm_size);
	while (getline(infile, one_input)) {
		if (counter % batch_num == 0) {
			this->set_0(AdUtil::str_join(batch_inputs, ",").c_str(), ",");
			batch_inputs.clear();
		}
		batch_inputs.push_back(one_input);
		counter++;
		
	}
	if (!batch_inputs.empty()) {
		this->set_0(AdUtil::str_join(batch_inputs, ",").c_str(), ",");
		batch_inputs.clear();
	}
	infile.close();

	return true;
}

void Bitmap::display(int n) {
	n = (n > bm_size) ? bm_size : n;
	for (int i = 0; i < n; i++) {
		int tmp = bitmap[i];
		std::string tmp_s = "";
		for (int j = 0; j < 8; j++) {
			tmp_s += " " + AdUtil::int_to_str(tmp & 1);
			tmp >>= 1;
		}
		printf("%s\n", tmp_s.c_str());
	}
}

