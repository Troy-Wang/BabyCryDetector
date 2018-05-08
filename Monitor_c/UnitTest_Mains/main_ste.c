#include <stdio.h>
#include "STE.h"

int main()
{
	double a[] = {1,2,3,4,5,6};
	double feature_ste,feature_steacc;
	
	STE(a,sizeof(a)/sizeof(double),100,8,&feature_ste,&feature_steacc);

	printf("%lf\t%lf\t",feature_ste,feature_steacc);

	printf("\n");

	return -1;
}
