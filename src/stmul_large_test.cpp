#include <stdio.h>
#include <math.h>
#include "stmul_large.h"
#include <inttypes.h>

uint_large_h gen_pattern_(uint_large_l power, int modulus){
	uint_large_h res = 0;
	int i = 0;
	for(i=0;i<power;i++){
		res = (uint_large_h)((uint_large_h)res | (uint_large_h)((uint_large_h)((i % modulus) & 1) << (uint_large_h)i));
	}
	return res;
}

uint_large_h calc_powerof_two_(uint_large_l power){
	uint_large_h res = 0;
	int i = 0;
	for(i=0;i<power;i++){
		res = (uint_large_h)((uint_large_h)res | (uint_large_h)((uint_large_h)1 << (uint_large_h)i));
	}
	return res;
}

int main () {
  const int    SAMPLES=11;
  FILE         *fp;
  FILE         *fp_calc;

  uint_large_h output;
  uint_large_h output_calc;
#define FULL_BIT calc_powerof_two_(MUL_LRG_LOW_WIDTH)
  uint_large_h a[SAMPLES] = {0,gen_pattern_(MUL_LRG_LOW_WIDTH, 2),gen_pattern_(MUL_LRG_LOW_WIDTH, 4),gen_pattern_(MUL_LRG_LOW_WIDTH, 6),
		  	  	  	    gen_pattern_(MUL_LRG_LOW_WIDTH, 2),gen_pattern_(MUL_LRG_LOW_WIDTH, 2),gen_pattern_(MUL_LRG_LOW_WIDTH, 2),
						gen_pattern_(MUL_LRG_LOW_WIDTH, 3),gen_pattern_(MUL_LRG_LOW_WIDTH, 8),gen_pattern_(MUL_LRG_LOW_WIDTH, 15),FULL_BIT};
  uint_large_h b[SAMPLES] = {0,gen_pattern_(MUL_LRG_LOW_WIDTH, 3),gen_pattern_(MUL_LRG_LOW_WIDTH, 5),gen_pattern_(MUL_LRG_LOW_WIDTH, 7),
		  	  	  	  	gen_pattern_(MUL_LRG_LOW_WIDTH, 7),gen_pattern_(MUL_LRG_LOW_WIDTH, 2),gen_pattern_(MUL_LRG_LOW_WIDTH, 2),
						gen_pattern_(MUL_LRG_LOW_WIDTH, 2),gen_pattern_(MUL_LRG_LOW_WIDTH, 2),gen_pattern_(MUL_LRG_LOW_WIDTH, 21),FULL_BIT};
  
  fp=fopen("out_large.dat","w");
  fp_calc=fopen("out_large.calc.dat","w");

  int numberOf32Bits = MUL_LRG_MAX_WIDTH / 32;

  int i;
  for (i=0;i<SAMPLES;i++) {
	large_mul(&output,a[i], b[i]);
	output_calc = (uint_large_h)((uint_large_h)a[i] * (uint_large_h)b[i]);
		// Save the results.
	int j=0;
	//printf("a : ");
	for (j=0;j<numberOf32Bits/2-1;j++){
		//printf("%d ",a[i].range(((j + 1) * 32) + 31, j*32));
		unsigned long t = a[i].range(((j + 1) * 32) + 31, j*32);
		//printf("%lX ",t);
		fprintf(fp,"%lX ",t);
		fprintf(fp_calc,"%lX ",t);
	}
	//printf(" , ");
	//printf("b : ");
	for (j=0;j<numberOf32Bits/2-1;j++){
		unsigned long t = b[i].range(((j + 1) * 32) + 31, j*32);
		//printf("%lX ",t);
		fprintf(fp,"%lX ",t);
		fprintf(fp_calc,"%lX ",t);
	}
	//printf(" , ");
	//printf("out : ");
	for (j=0;j<numberOf32Bits-1;j++){
		unsigned long t = output.range(((j + 1) * 32) + 31, j*32);
		unsigned long tcalc = output_calc.range(((j + 1) * 32) + 31, j*32);
		//printf("%lX ",t);
		fprintf(fp,"%lX ",t);
		fprintf(fp_calc,"%lX ",tcalc);
	}
	//printf("\n");
	fprintf(fp,"\n");
	fprintf(fp_calc,"\n");
    //unsigned long long ans1 = a[i];
    //unsigned long long ans2 = b[i];
    //unsigned long long ans3 = output.range(MUL_LRG_LOW_WIDTH-1, 0); //apint_get_range(output, MUL_LRG_LOW_WIDTH-1, 0);
    //unsigned long long ans4 = output.range(MUL_LRG_MAX_WIDTH-1, MUL_LRG_LOW_WIDTH); //apint_get_range(output, MUL_LRG_MAX_WIDTH-1, MUL_LRG_LOW_WIDTH);
    //printf("Output : %llX\n",output);
    //printf("Output calc : %llX\n",output_calc);
    //fprintf(fp,"%i %llX %llX %llX %llX\n",i, ans1, ans2, ans3, ans4);
    //fprintf(fp_calc,"%i %llX %llX %llX %llX\n",i, ans1, ans2, apint_get_range(output_calc, MUL_LRG_LOW_WIDTH-1, 0), apint_get_range(output_calc, MUL_LRG_MAX_WIDTH-1, MUL_LRG_LOW_WIDTH));
    //fprintf(fp_calc,"%i %llX %llX %llX %llX\n",i, ans1, ans2, output_calc.range(MUL_LRG_LOW_WIDTH-1, 0), output_calc.range(MUL_LRG_MAX_WIDTH-1, MUL_LRG_LOW_WIDTH));

  }
  fclose(fp);
  fclose(fp_calc);
  
  printf ("Comparing against output data \n");
  if (system("diff -w out_large.dat out_large.calc.dat")) {

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
