#include "stmul.h"
#define SCHOOL_BOOK
//#define DIRECT_MULTIPLIER
#ifndef DIRECT_MULTIPLIER
uintl mult(uintlhalf x, uintlhalf y){
	uintl m1 = (uintl)((uintl)x * (uintl)y);
	return m1;
}

uintl add(uintlhalf x, uintlhalf y, uintlhalf c){
#ifdef PIPELINE_ADDER
	uintl s1 = (uintl)x + (uintl)y;
	return (uintl)((uintl)s1 + (uintl)c);
#else
	uintl s1 = (uintl)((uintl)x + (uintl)y + (uintl)c);
	return s1;
#endif
}
#else
uinth mult(uinth x, uinth y){
//#pragma HLS RESOURCE variable=return core=Mul_LUT
	uinth m1 = (uinth)((uinth)x * (uinth)y);
	return m1;
}
#endif

void mul (
		uinth *y,
		uintlhalf a_0,
		uintlhalf a_1,
		uintlhalf b_0,
		uintlhalf b_1
		//uintl a,
		//uintl b
  ) {

#ifdef DIRECT_MULTIPLIER
	uinth a =  (uinth)((uinth)((uinth)a_1 << MUL_HALF_WIDTH) |
					   (uinth)((uinth)a_0));
	uinth b =  (uinth)((uinth)((uinth)b_1 << MUL_HALF_WIDTH) |
					   (uinth)((uinth)b_0));
	*y = mult(a, b); // Direct multiplier
#else

	//			AB  (a)
	//X			CD  (b)
	//--------------
	//       [ DB ]
	//     [ DA ]
	//     [ CB ]
	//  [ CA ]
	//--------------
	//  [ Y1 ][ Y0 ]

	//uintlhalf ma_0 = a_0;
	//uintlhalf ma_1 = a_1;
	//uintlhalf mb_0 = b_0;
	//uintlhalf mb_1 = b_1;

	//uintl m1, m2, m3, m4, a1, a2, a3, a4, a5;
	//uintlhalf a1_l, a1_c, a2_l, a2_c, a3_l, a3_c,a4_l, a4_c,a5_l;
	//uintlhalf m1_h, m1_l, m2_h, m2_l, m3_h, m3_l, m4_h, m4_l;

	// State 1 :
	// Op : D*B, A*D
	uintl m1 = mult(a_0, b_0);
	uintl m2 = mult(a_0, b_1);

	uintlhalf m1_h = m1.range(MUL_LOW_WIDTH-1,MUL_HALF_WIDTH);
	uintlhalf m1_l = m1.range(MUL_HALF_WIDTH-1,0);

	uintlhalf m2_h = m2.range(MUL_LOW_WIDTH-1,MUL_HALF_WIDTH);
	uintlhalf m2_l = m2.range(MUL_HALF_WIDTH-1,0);

	// Op : m1_h + m2_l
	uintl a1 = add(m1_h, m2_l, 0);
	uintlhalf a1_l = a1.range(MUL_HALF_WIDTH-1,0);
	uintlhalf a1_c = a1.range(MUL_LOW_WIDTH-1,MUL_HALF_WIDTH);

	// Op : C*B, C*A
	uintl m3 = mult(a_1, b_0);
	uintl m4 = mult(a_1, b_1);

	uintlhalf m3_h = m3.range(MUL_LOW_WIDTH-1,MUL_HALF_WIDTH);
	uintlhalf m3_l = m3.range(MUL_HALF_WIDTH-1,0);

	uintlhalf m4_h = m4.range(MUL_LOW_WIDTH-1,MUL_HALF_WIDTH);
	uintlhalf m4_l = m4.range(MUL_HALF_WIDTH-1,0);

	// Op : m2_h + m3_h + a1_c
	uintl a2 = add(m2_h, m3_h, a1_c);
	uintlhalf a2_l = a2.range(MUL_HALF_WIDTH-1,0);
	uintlhalf a2_c = a2.range(MUL_LOW_WIDTH-1,MUL_HALF_WIDTH);

	// Op : m3_l + a1_l
	uintl a3 = add(m3_l, a1_l, 0);
	uintlhalf a3_l = a3.range(MUL_HALF_WIDTH-1,0);
	uintlhalf a3_c = a3.range(MUL_LOW_WIDTH-1,MUL_HALF_WIDTH);

	// Op : m4_l + a2_l + a3_c
	uintl a4 = add(m4_l, a2_l, a3_c);
	uintlhalf a4_l = a4.range(MUL_HALF_WIDTH-1,0);
	uintlhalf a4_c = a4.range(MUL_LOW_WIDTH-1,MUL_HALF_WIDTH);

	// Op : m4_h + a2_c + a4_c
	uintl a5 = add(m4_h, a2_c, a4_c);
	uintlhalf a5_l = a5.range(MUL_HALF_WIDTH-1,0);

	*y = (uinth)((uinth)a5_l << (MUL_LOW_WIDTH + MUL_HALF_WIDTH)) | (uinth)((uinth)a4_l << MUL_LOW_WIDTH) | (uinth)((uinth)a3_l << MUL_HALF_WIDTH) | (uinth)m1_l;
#endif
}


