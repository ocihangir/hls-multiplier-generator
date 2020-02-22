#ifndef LRG_MUL_
#define LRG_MUL_
#define AP_INT_MAX_W 8192          // Must be defined before next line
#include <ap_int.h>
#include "stmul.h"

//DEFINE_DIRECT_MULTIPLIER

//DEFINE_LRG_WIDTH
#define LRG_WIDTH4096
//#define LRG_WIDTH256

#ifdef LRG_WIDTH16

#define MUL_LRG_MAX_WIDTH 16

typedef ap_uint<16> uint_large_h;
typedef ap_uint<8> uint_large_l;
typedef ap_uint<4> uintl_large_half;

#endif

#ifdef LRG_WIDTH32

#define MUL_LRG_MAX_WIDTH 32

typedef ap_uint<32> uint_large_h;
typedef ap_uint<16> uint_large_l;
typedef ap_uint<8> uintl_large_half;

#endif

#ifdef LRG_WIDTH64

#define MUL_LRG_MAX_WIDTH 64

typedef ap_uint<64> uint_large_h;
typedef ap_uint<32> uint_large_l;
typedef ap_uint<16> uintl_large_half;

#endif

#ifdef LRG_WIDTH128

#define MUL_LRG_MAX_WIDTH 128

typedef ap_uint<128> uint_large_h;
typedef ap_uint<64> uint_large_l;
typedef ap_uint<32> uintl_large_half;

#endif

#ifdef LRG_WIDTH256

#define MUL_LRG_MAX_WIDTH 256

typedef ap_uint<256> uint_large_h;
typedef ap_uint<128> uint_large_l;
typedef ap_uint<64> uintl_large_half;

#endif

#ifdef LRG_WIDTH512

#define MUL_LRG_MAX_WIDTH 512

typedef ap_uint<512> uint_large_h;
typedef ap_uint<256> uint_large_l;
typedef ap_uint<128> uintl_large_half;

#endif

#ifdef LRG_WIDTH1024

#define MUL_LRG_MAX_WIDTH 1024

typedef ap_uint<1024> uint_large_h;
typedef ap_uint<512> uint_large_l;
typedef ap_uint<256> uintl_large_half;

#endif

#ifdef LRG_WIDTH2048

#define MUL_LRG_MAX_WIDTH 2048

typedef ap_uint<2048> uint_large_h;
typedef ap_uint<1024> uint_large_l;
typedef ap_uint<512> uintl_large_half;

#endif

#ifdef LRG_WIDTH4096

#define MUL_LRG_MAX_WIDTH 4096

typedef ap_uint<4096> uint_large_h;
typedef ap_uint<2048> uint_large_l;
typedef ap_uint<1024> uintl_large_half;

#endif

#ifdef LRG_WIDTH8192

#define MUL_LRG_MAX_WIDTH 8192

typedef ap_uint<8192> uint_large_h;
typedef ap_uint<4096> uint_large_l;
typedef ap_uint<2048> uintl_large_half;

#endif

#define MUL_LRG_LOW_WIDTH MUL_LRG_MAX_WIDTH/2
#define MUL_LRG_HALF_WIDTH MUL_LRG_LOW_WIDTH/2



void large_mul (
	uint_large_h *y,
	uint_large_l a,
	uint_large_l b
  );

#endif
