//
// Created by 丁磊 on 2019/9/17.
//

#ifndef STOCKOUT_FILTER_BITMAP2_H
#define STOCKOUT_FILTER_BITMAP2_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "../interfaces/EventHandler.h"

/*
	2147483647对应16进制0x7fffffff， 对应二进制1...1...1(31个)
	1999999999对应16进制0x773593ff

	#define BIT_CAPACITY 2147483650
*/
#define BIT_CAPACITY 2000000000

class Bitmap : public AutoUpdate {
public:
	Bitmap(const char* gds_file);
	~Bitmap();

  /*
	传入数据格式：商品编码1 商户编码1 地区编码1,  商品编码2 商户编码2 地区编码2,......
	101070521  0000000000 000001000024,  101070521 0000000000 000001000237
	一条记录用空格连接按商品+商户+地区串接，
	多条记录用除空格以外的分隔符连接连接，如逗号
  */
  void set_1(const char* keys, const char* delim=",");
  void set_0(const char* keys, const char* delim=",");
  char * get(const char* keys, const char* delim=",");

  void display(int n);
  bool Update();
//  int test(const char* test_files, int flag);

private:
  size_t bm_size;
  unsigned char* bitmap;
  std::string gds_file_str;
};

#endif //STOCKOUT_FILTER_BITMAP2_H
