#define AP_INT_MAX_W 8192          // Must be defined before next line
#include <ap_int.h>
#include <hls_stream.h>
#include "stmul_large.h"

uinth unit_mult(uintlhalf a_0, uintlhalf a_1, uintlhalf b_0, uintlhalf b_1){
	uinth o;
	mul(&o,a_0,a_1,b_0,b_1);
	return o;
}

#ifndef DIRECT_MULTIPLIER
uint_large_h adder(uint_large_h a, uint_large_h b){
	uint_large_h result;
	result = a + b;
	return result;
}
#else
uint_large_h direct_mult(uint_large_l x, uint_large_l y){
#pragma HLS RESOURCE variable=return core=Mul_LUT
	return (uint_large_h)x * (uint_large_h)y;
}
#endif

void large_mul (
		uint_large_h *y,
		uint_large_l a,
		uint_large_l b
  ) {
#ifdef DIRECT_MULTIPLIER
	*y = direct_mult(a,b);
#else

//GENERATED_MULTIPLIER

uintlhalf in_op0_0 = a.range(127,0);
uintlhalf in_op0_128 = a.range(255,128);
uintlhalf in_op0_256 = a.range(383,256);
uintlhalf in_op0_384 = a.range(511,384);
uintlhalf in_op0_512 = a.range(639,512);
uintlhalf in_op0_640 = a.range(767,640);
uintlhalf in_op0_768 = a.range(895,768);
uintlhalf in_op0_896 = a.range(1023,896);
uintlhalf in_op0_1024 = a.range(1151,1024);
uintlhalf in_op0_1152 = a.range(1279,1152);
uintlhalf in_op0_1280 = a.range(1407,1280);
uintlhalf in_op0_1408 = a.range(1535,1408);
uintlhalf in_op0_1536 = a.range(1663,1536);
uintlhalf in_op0_1664 = a.range(1791,1664);
uintlhalf in_op0_1792 = a.range(1919,1792);
uintlhalf in_op0_1920 = a.range(2047,1920);

uintlhalf in_op1_0 = b.range(127,0);
uintlhalf in_op1_128 = b.range(255,128);
uintlhalf in_op1_256 = b.range(383,256);
uintlhalf in_op1_384 = b.range(511,384);
uintlhalf in_op1_512 = b.range(639,512);
uintlhalf in_op1_640 = b.range(767,640);
uintlhalf in_op1_768 = b.range(895,768);
uintlhalf in_op1_896 = b.range(1023,896);
uintlhalf in_op1_1024 = b.range(1151,1024);
uintlhalf in_op1_1152 = b.range(1279,1152);
uintlhalf in_op1_1280 = b.range(1407,1280);
uintlhalf in_op1_1408 = b.range(1535,1408);
uintlhalf in_op1_1536 = b.range(1663,1536);
uintlhalf in_op1_1664 = b.range(1791,1664);
uintlhalf in_op1_1792 = b.range(1919,1792);
uintlhalf in_op1_1920 = b.range(2047,1920);

// Unit multiplier outputs
//uint_large_h output[64];
uint_large_h tmp_output = 0;

// Unit multiplier 0
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_0, in_op0_128, in_op1_0, in_op1_128) << 0 ));
// Unit multiplier 1
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_0, in_op0_128, in_op1_256, in_op1_384) << 256 ));
// Unit multiplier 8
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_256, in_op0_384, in_op1_0, in_op1_128) << 256 ));
// Unit multiplier 2
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_0, in_op0_128, in_op1_512, in_op1_640) << 512 ));
// Unit multiplier 9
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_256, in_op0_384, in_op1_256, in_op1_384) << 512 ));
// Unit multiplier 16
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_512, in_op0_640, in_op1_0, in_op1_128) << 512 ));
// Unit multiplier 3
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_0, in_op0_128, in_op1_768, in_op1_896) << 768 ));
// Unit multiplier 10
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_256, in_op0_384, in_op1_512, in_op1_640) << 768 ));
// Unit multiplier 17
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_512, in_op0_640, in_op1_256, in_op1_384) << 768 ));
// Unit multiplier 24
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_768, in_op0_896, in_op1_0, in_op1_128) << 768 ));
// Unit multiplier 4
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_0, in_op0_128, in_op1_1024, in_op1_1152) << 1024 ));
// Unit multiplier 11
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_256, in_op0_384, in_op1_768, in_op1_896) << 1024 ));
// Unit multiplier 18
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_512, in_op0_640, in_op1_512, in_op1_640) << 1024 ));
// Unit multiplier 25
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_768, in_op0_896, in_op1_256, in_op1_384) << 1024 ));
// Unit multiplier 32
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1024, in_op0_1152, in_op1_0, in_op1_128) << 1024 ));
// Unit multiplier 5
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_0, in_op0_128, in_op1_1280, in_op1_1408) << 1280 ));
// Unit multiplier 12
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_256, in_op0_384, in_op1_1024, in_op1_1152) << 1280 ));
// Unit multiplier 19
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_512, in_op0_640, in_op1_768, in_op1_896) << 1280 ));
// Unit multiplier 26
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_768, in_op0_896, in_op1_512, in_op1_640) << 1280 ));
// Unit multiplier 33
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1024, in_op0_1152, in_op1_256, in_op1_384) << 1280 ));
// Unit multiplier 40
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1280, in_op0_1408, in_op1_0, in_op1_128) << 1280 ));
// Unit multiplier 6
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_0, in_op0_128, in_op1_1536, in_op1_1664) << 1536 ));
// Unit multiplier 13
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_256, in_op0_384, in_op1_1280, in_op1_1408) << 1536 ));
// Unit multiplier 20
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_512, in_op0_640, in_op1_1024, in_op1_1152) << 1536 ));
// Unit multiplier 27
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_768, in_op0_896, in_op1_768, in_op1_896) << 1536 ));
// Unit multiplier 34
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1024, in_op0_1152, in_op1_512, in_op1_640) << 1536 ));
// Unit multiplier 41
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1280, in_op0_1408, in_op1_256, in_op1_384) << 1536 ));
// Unit multiplier 48
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1536, in_op0_1664, in_op1_0, in_op1_128) << 1536 ));
// Unit multiplier 7
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_0, in_op0_128, in_op1_1792, in_op1_1920) << 1792 ));
// Unit multiplier 14
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_256, in_op0_384, in_op1_1536, in_op1_1664) << 1792 ));
// Unit multiplier 21
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_512, in_op0_640, in_op1_1280, in_op1_1408) << 1792 ));
// Unit multiplier 28
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_768, in_op0_896, in_op1_1024, in_op1_1152) << 1792 ));
// Unit multiplier 35
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1024, in_op0_1152, in_op1_768, in_op1_896) << 1792 ));
// Unit multiplier 42
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1280, in_op0_1408, in_op1_512, in_op1_640) << 1792 ));
// Unit multiplier 49
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1536, in_op0_1664, in_op1_256, in_op1_384) << 1792 ));
// Unit multiplier 56
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1792, in_op0_1920, in_op1_0, in_op1_128) << 1792 ));
// Unit multiplier 15
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_256, in_op0_384, in_op1_1792, in_op1_1920) << 2048 ));
// Unit multiplier 22
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_512, in_op0_640, in_op1_1536, in_op1_1664) << 2048 ));
// Unit multiplier 29
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_768, in_op0_896, in_op1_1280, in_op1_1408) << 2048 ));
// Unit multiplier 36
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1024, in_op0_1152, in_op1_1024, in_op1_1152) << 2048 ));
// Unit multiplier 43
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1280, in_op0_1408, in_op1_768, in_op1_896) << 2048 ));
// Unit multiplier 50
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1536, in_op0_1664, in_op1_512, in_op1_640) << 2048 ));
// Unit multiplier 57
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1792, in_op0_1920, in_op1_256, in_op1_384) << 2048 ));
// Unit multiplier 23
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_512, in_op0_640, in_op1_1792, in_op1_1920) << 2304 ));
// Unit multiplier 30
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_768, in_op0_896, in_op1_1536, in_op1_1664) << 2304 ));
// Unit multiplier 37
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1024, in_op0_1152, in_op1_1280, in_op1_1408) << 2304 ));
// Unit multiplier 44
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1280, in_op0_1408, in_op1_1024, in_op1_1152) << 2304 ));
// Unit multiplier 51
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1536, in_op0_1664, in_op1_768, in_op1_896) << 2304 ));
// Unit multiplier 58
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1792, in_op0_1920, in_op1_512, in_op1_640) << 2304 ));
// Unit multiplier 31
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_768, in_op0_896, in_op1_1792, in_op1_1920) << 2560 ));
// Unit multiplier 38
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1024, in_op0_1152, in_op1_1536, in_op1_1664) << 2560 ));
// Unit multiplier 45
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1280, in_op0_1408, in_op1_1280, in_op1_1408) << 2560 ));
// Unit multiplier 52
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1536, in_op0_1664, in_op1_1024, in_op1_1152) << 2560 ));
// Unit multiplier 59
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1792, in_op0_1920, in_op1_768, in_op1_896) << 2560 ));
// Unit multiplier 39
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1024, in_op0_1152, in_op1_1792, in_op1_1920) << 2816 ));
// Unit multiplier 46
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1280, in_op0_1408, in_op1_1536, in_op1_1664) << 2816 ));
// Unit multiplier 53
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1536, in_op0_1664, in_op1_1280, in_op1_1408) << 2816 ));
// Unit multiplier 60
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1792, in_op0_1920, in_op1_1024, in_op1_1152) << 2816 ));
// Unit multiplier 47
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1280, in_op0_1408, in_op1_1792, in_op1_1920) << 3072 ));
// Unit multiplier 54
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1536, in_op0_1664, in_op1_1536, in_op1_1664) << 3072 ));
// Unit multiplier 61
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1792, in_op0_1920, in_op1_1280, in_op1_1408) << 3072 ));
// Unit multiplier 55
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1536, in_op0_1664, in_op1_1792, in_op1_1920) << 3328 ));
// Unit multiplier 62
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1792, in_op0_1920, in_op1_1536, in_op1_1664) << 3328 ));
// Unit multiplier 63
tmp_output = adder(tmp_output,(uint_large_h)((uint_large_h)unit_mult(in_op0_1792, in_op0_1920, in_op1_1792, in_op1_1920) << 3584 ));

//*y =  + output[0] + output[1] + output[2] + output[3] + output[4] + output[5] + output[6] + output[7] + output[8] + output[9] + output[10] + output[11] + output[12] + output[13] + output[14] + output[15] + output[16] + output[17] + output[18] + output[19] + output[20] + output[21] + output[22] + output[23] + output[24] + output[25] + output[26] + output[27] + output[28] + output[29] + output[30] + output[31] + output[32] + output[33] + output[34] + output[35] + output[36] + output[37] + output[38] + output[39] + output[40] + output[41] + output[42] + output[43] + output[44] + output[45] + output[46] + output[47] + output[48] + output[49] + output[50] + output[51] + output[52] + output[53] + output[54] + output[55] + output[56] + output[57] + output[58] + output[59] + output[60] + output[61] + output[62] + output[63];
*y = tmp_output;


#endif
}
