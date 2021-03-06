#ifndef FIR_H_
#define FIR_H_
#define AP_INT_MAX_W 8192          // Must be defined before next line
#include <ap_int.h>

//DEFINE_DIRECT_MULTIPLIER
//DEFINE_WIDTH
#define WIDTH512
//#define DIRECT_MULTIPLIER
//#define WIDTH16

#ifdef WIDTH4

#define MUL_MAX_WIDTH 4
#define NUMBEROF32BITOP 1
#define NUMBEROF32BITRES 1

typedef ap_uint<4> uinth;
typedef ap_uint<2> uintl;
typedef ap_uint<1> uintlhalf;

#endif

#ifdef WIDTH8

#define MUL_MAX_WIDTH 8
#define NUMBEROF32BITOP 1
#define NUMBEROF32BITRES 1

typedef ap_uint<8> uinth;
typedef ap_uint<4> uintl;
typedef ap_uint<2> uintlhalf;

#endif

#ifdef WIDTH16

#define MUL_MAX_WIDTH 16
#define NUMBEROF32BITOP 1
#define NUMBEROF32BITRES 1

typedef ap_uint<16> uinth;
typedef ap_uint<8> uintl;
typedef ap_uint<4> uintlhalf;

#endif

#ifdef WIDTH32

#define MUL_MAX_WIDTH 32
#define NUMBEROF32BITOP 1
#define NUMBEROF32BITRES 1

typedef ap_uint<32> uinth;
typedef ap_uint<16> uintl;
typedef ap_uint<8> uintlhalf;

#endif

#ifdef WIDTH64

#define MUL_MAX_WIDTH 64
#define NUMBEROF32BITOP 1
#define NUMBEROF32BITRES 2

typedef ap_uint<64> uinth;
typedef ap_uint<32> uintl;
typedef ap_uint<16> uintlhalf;

#endif

#ifdef WIDTH128

#define MUL_MAX_WIDTH 128
#define NUMBEROF32BITOP 2
#define NUMBEROF32BITRES 4

typedef ap_uint<128> uinth;
typedef ap_uint<64> uintl;
typedef ap_uint<32> uintlhalf;

#endif

#ifdef WIDTH256

#define MUL_MAX_WIDTH 256
#define NUMBEROF32BITOP 4
#define NUMBEROF32BITRES 8

typedef ap_uint<256> uinth;
typedef ap_uint<128> uintl;
typedef ap_uint<64> uintlhalf;

#endif

#ifdef WIDTH512

#define MUL_MAX_WIDTH 512
#define NUMBEROF32BITOP 8
#define NUMBEROF32BITRES 16

typedef ap_uint<512> uinth;
typedef ap_uint<256> uintl;
typedef ap_uint<128> uintlhalf;

#endif

#ifdef WIDTH1024

#define MUL_MAX_WIDTH 1024
#define NUMBEROF32BITOP 16
#define NUMBEROF32BITRES 32

typedef ap_uint<1024> uinth;
typedef ap_uint<512> uintl;
typedef ap_uint<256> uintlhalf;

#endif

#define MUL_LOW_WIDTH MUL_MAX_WIDTH/2
#define MUL_HALF_WIDTH MUL_LOW_WIDTH/2



void mul (
	uinth *y,
	uintlhalf a_0,
	uintlhalf a_1,
	uintlhalf b_0,
	uintlhalf b_1
  );

#endif
