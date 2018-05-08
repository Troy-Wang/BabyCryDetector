#include "absfft.h"
#include <stdio.h>

int main()
{
	int i;
	double a[] = {1,2,3,4,5,6};
	double *fftres;
	int resSize;
	absfft(a,sizeof(a)/sizeof(double),&fftres,&resSize);
	for(i=0;i<resSize;i++)
		printf("%lf\t",fftres[i]);
	printf("\n");
	return 1;
}
