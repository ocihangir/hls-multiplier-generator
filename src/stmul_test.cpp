#include <stdio.h>
#include <math.h>
#include "stmul.h"
#include <inttypes.h>

uintl gen_pattern(uintl power, int modulus){
	uintl res = 0;
	int i = 0;
	for(i=0;i<power;i++){
		res = (uintl)((uintl)res | (uintl)((uintl)((i % modulus) & 1) << (uintl)i));
	}
	return res;
}

uintl calc_powerof_two(uintl power){
	uintl res = 0;
	int i = 0;
	for(i=0;i<power;i++){
		res = (uintl)((uintl)res | (uintl)((uintl)1 << (uintl)i));
	}
	return res;
}

int main () {
  const int    SAMPLES=11;
  FILE         *fp;
  FILE         *fp_calc;

  uinth output;
  //uinth output_calc;
#define FULL_BIT calc_powerof_two(MUL_LOW_WIDTH)
#ifdef WIDTH8
  uintl a[SAMPLES] = {0,0x1,0x2,0x3,0xF,0xC,0x9,0xE,0xC,FULL_BIT};
  uintl b[SAMPLES] = {0,0x1,0x2,0x3,0xA,0x4,0xA,0x2,0xD,FULL_BIT};
#endif
#ifdef WIDTH16
  uintl a[SAMPLES] = {0,0x1,0x2,0x3,0xFE,0x23,0x10,0x22,0xAB,FULL_BIT};
  uintl b[SAMPLES] = {0,0xFE,0xDC,0x32,0x23,0x64,0xAA,0xCC,0xBB,FULL_BIT};
#endif
#ifdef WIDTH32
  uintl a[SAMPLES] = {0,0x1,0x2,0x3,0xFE,0x23,0x10,0x22,0xAB,FULL_BIT};
  uintl b[SAMPLES] = {0,0xFE,0xDC,0x32,0x23,0x64,0xAA,0xCC,0xBB,FULL_BIT};
#endif
#ifdef WIDTH64
  uintl a[SAMPLES] = {0,1,2,3,255,128,134,177,232,FULL_BIT};
  uintl b[SAMPLES] = {0,232,123,245,10,22,33,17,222,FULL_BIT};
#endif
//#else
//  uintl a[SAMPLES] = {0,0x1,0x2,0x3,0xF,0xC,0x9,0xE,0xC,FULL_BIT};
//  uintl b[SAMPLES] = {0,0x1,0x2,0x3,0xA,0x4,0xA,0x2,0xD,FULL_BIT};
//#endif

  
  fp=fopen("out.dat","w");
  //fp_calc=fopen("out.calc.dat","w");
  int i;
  for (i=0;i<SAMPLES;i++) {

	// Execute the function with latest input
	uintlhalf a_h = a[i].range(MUL_LOW_WIDTH-1, MUL_HALF_WIDTH);
	uintlhalf a_l = a[i].range(MUL_HALF_WIDTH-1, 0);
	uintlhalf b_h = b[i].range(MUL_LOW_WIDTH-1, MUL_HALF_WIDTH);
	uintlhalf b_l = b[i].range(MUL_HALF_WIDTH-1, 0);
    //mul(&output,a[i],b[i]);
	mul(&output,a_l, a_h, a_l,a_h,b_l,b_l,b_h,b_h);
	//output_calc = a[i]*b[i];
		// Save the results.
		fprintf(fp,"%i ", i);
		for(int j=NUMBEROF32BITOP;j>0;j--){
			fprintf(fp, "%x", (int)a[i].range(j*32,(j-1)*32));
		}
		fprintf(fp, " ");
		for(int j=NUMBEROF32BITOP;j>0;j--){
			fprintf(fp, "%x", (int)b[i].range(j*32,(j-1)*32));
		}
		fprintf(fp, " ");
		for(int j=NUMBEROF32BITRES;j>0;j--){
			fprintf(fp, "%x ", (int)output.range(j*32,(j-1)*32));
		}
		fprintf(fp, "\n");
    //unsigned long long ans1 = a[i];
    //unsigned long long ans2 = b[i];
    //unsigned long long ans3 = output.range(MUL_LOW_WIDTH-1, 0);
    //unsigned long long ans4 = output.range(MUL_MAX_WIDTH-1, MUL_LOW_WIDTH);
    //printf("Output : %llX\n",output_calc);
    //fprintf(fp,"%i %llX %llX %llX %llX\n",i, ans1, ans2, ans3, ans4);
    //fprintf(fp_calc,"%i %llX %llX %llX %llX\n",i, ans1, ans2, output_calc.range(MUL_LOW_WIDTH-1, 0), output_calc.range(MUL_MAX_WIDTH-1, MUL_LOW_WIDTH));
  }
  fclose(fp);
  //fclose(fp_calc);
  
  printf ("Comparing against output data \n");
  if (system("diff -w out.dat out.calc.dat")) {

	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
	fprintf(stdout, "*******************************************\n");
     return 1;
  } else {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "PASS: The output matches the golden output!\n");
	fprintf(stdout, "*******************************************\n");
     return 0;
  }
}
