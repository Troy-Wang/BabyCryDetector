#include <stdio.h>
#include "mean.h"

int main()
{
	double a[] = {1,2,3};
	int size = sizeof(a)/sizeof(double);
	printf("%lf\n",mean(a,size));
}
