#include <stdio.h>
#include "PitchFreq.h"

int main()
{
	double a[] = {1,2,3,4,5,6};
	int feature_pf1;
	double feature_pf2;

	PitchFreq(a,sizeof(a)/sizeof(double),100,8,&feature_pf1,&feature_pf2); 
	
	printf("%d\t%lf\t",feature_pf1,feature_pf2);

	return 1;
}
