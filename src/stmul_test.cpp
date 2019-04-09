#include <stdio.h>
#include <math.h>
#include "stmul.h"
#include <inttypes.h>

uinth gen_pattern(uintl power, int modulus){
	uinth res = 0;
	int i = 0;
	for(i=0;i<power;i++){
		res = (uinth)((uinth)res | (uinth)((uinth)((i % modulus) & 1) << (uinth)i));
	}
	return res;
}

uinth calc_powerof_two(uintl power){
	uinth res = 0;
	int i = 0;
	for(i=0;i<power;i++){
		res = (uinth)((uinth)res | (uinth)((uinth)1 << (uinth)i));
	}
	return res;
}

int main () {
  const int    SAMPLES=11;
  FILE         *fp;
  FILE         *fp_calc;

  uinth output;
  uinth output_calc;
#define FULL_BIT calc_powerof_two(MUL_LOW_WIDTH)
  uinth a[SAMPLES] = {0,gen_pattern(MUL_LOW_WIDTH, 2),gen_pattern(MUL_LOW_WIDTH, 4),gen_pattern(MUL_LOW_WIDTH, 6),
		  	  	  	    gen_pattern(MUL_LOW_WIDTH, 2),gen_pattern(MUL_LOW_WIDTH, 2),gen_pattern(MUL_LOW_WIDTH, 2),
						gen_pattern(MUL_LOW_WIDTH, 3),gen_pattern(MUL_LOW_WIDTH, 8),gen_pattern(MUL_LOW_WIDTH, 15),FULL_BIT};
  uinth b[SAMPLES] = {0,gen_pattern(MUL_LOW_WIDTH, 3),gen_pattern(MUL_LOW_WIDTH, 5),gen_pattern(MUL_LOW_WIDTH, 7),
		  	  	  	  	gen_pattern(MUL_LOW_WIDTH, 7),gen_pattern(MUL_LOW_WIDTH, 2),gen_pattern(MUL_LOW_WIDTH, 2),
						gen_pattern(MUL_LOW_WIDTH, 2),gen_pattern(MUL_LOW_WIDTH, 2),gen_pattern(MUL_LOW_WIDTH, 21),FULL_BIT};
  
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
	output_calc = ((uinth)a[i] * (uinth)b[i]);
		// Save the results.
    unsigned long long ans1 = a[i];
    unsigned long long ans2 = b[i];
    unsigned long long ans3 = output.range(MUL_LOW_WIDTH-1, 0);
    unsigned long long ans4 = output.range(MUL_MAX_WIDTH-1, MUL_LOW_WIDTH);
    printf("Output : %llX\n",output);
    fprintf(fp,"%i %llX %llX %llX %llX\n",i, ans1, ans2, ans3, ans4);
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
