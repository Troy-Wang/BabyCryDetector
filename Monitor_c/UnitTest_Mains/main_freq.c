#include <stdio.h>
#include "Freq.h"

int main()
{
	double a[] = {1,2,3,4,5,6};
	
	double feature_Freq = Freq(a,sizeof(a)/sizeof(double),100,8);

	printf("%lf\n",feature_Freq);

	return 1;
}
