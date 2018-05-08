#include <stdio.h>

int main()
{
	double a[] = {1,-2,3,-4,5,-6};
	
	int feature_ZCR = ZCR(a,sizeof(a)/sizeof(double),150,8);

	printf("%d\n",feature_ZCR);
}
