#include "mean.h"

double mean(double *data, int size)
{
	int i;
	double sum=0, mean;
	for(i=0; i<size; i++)
		sum += data[i];
	mean = sum/size;
	return mean;
}
