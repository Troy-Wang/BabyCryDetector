#include <stdio.h>
#include "fir.h"
#include <malloc.h>

int main()
{
	int i;
	double a[] ={1,2,3,4,5,6};

	double *firData;
	firData = (double *)malloc(sizeof(double)*sizeof(a)/sizeof(double));
	fir(a,sizeof(a)/sizeof(double),firData);

	for(i=0;i<sizeof(a)/sizeof(double);i++)
		printf("%lf\n",firData[i]);
}
