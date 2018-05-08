#include <stdio.h>
#include "max.h"

int main()
{
	double a[]={1,2,3,4,5,6};
	int maxpos;
	
	double maximum = max(a,sizeof(a)/sizeof(int),3,5,&maxpos);

	printf("%lf\t%d\t",maximum,maxpos);	

	return 1;
}
