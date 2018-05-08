#include "medfilt3.h"
#include <malloc.h>

double median(double a, double b, double c)
{
	if ((a-b)*(a-c)<=0)
		return a;
	else if ((b-a)*(b-c)<=0)
		return b;
	else if ((c-a)*(c-b)<=0)
		return c;
}

/* 3 point median filter*/
void medfilt3(double *data, int size, double **medfilted)
{
	int i;
	double *medfiltedTemp = (double *)malloc(sizeof(double)*size);
	
	medfiltedTemp[0] = data[0];
	medfiltedTemp[size-1] = data[size-1];
	
	for(i=1; i<size-1; i++)
	{
		medfiltedTemp[i] = median(data[i-1],data[i],data[i+1]);
	}
	
	*medfilted = medfiltedTemp;
}
