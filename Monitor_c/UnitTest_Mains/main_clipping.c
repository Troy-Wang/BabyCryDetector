#include "clipping.h"
#include <stdio.h>

int main()
{
	int i;
	double a[] = {100,68,69,-69,-68,4,-4,99,-99,-55,55};
	double *clipped = NULL;
	
	clipping(a,sizeof(a)/sizeof(double),1,&clipped);
	for(i=0;i<sizeof(a)/sizeof(double);i++)
	{
		printf("%lf\t",clipped[i]);
	}
	printf("\n");
	return 1;
}
