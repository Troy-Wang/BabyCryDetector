#include <stdio.h>
#include "smoothing.h"

int main()
{
	int i;
	double a[] = {1,99,7,3,4,5};
	double *smoothedData = NULL;
	
	smoothing(a,sizeof(a)/sizeof(double),&smoothedData);

	for(i=0;i<sizeof(a)/sizeof(double);i++)
		printf("%lf\t",smoothedData[i]);
	printf("\n");
	
	return 1;
}
