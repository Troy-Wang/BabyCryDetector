#include "clipping.h"
#include "max.h"
#include <malloc.h>

int clipping(double data[], int size, int category, double **clippedData)
{
	int max_pos;
	double maximum = max(data,size,1,-1,&max_pos);
	double coeff = 0.68;
	double threshold = coeff*maximum;
	int i,k;
	double *clipped = (double *)malloc(sizeof(double)*size);

	if(category == 1)	// 3 level clipping
		for(i=0; i<size; i++)
			if(data[i]>=threshold)
				clipped[i] = 1;
			else if(data[i]<=0.00-threshold)
				clipped[i] = -1;
			else
				clipped[i] = 0;
	else if(category == 2)	//center clipping
		for(i=0; i<size; i++)
			if(data[i]>=threshold)
				clipped[i]=data[i]-threshold;
			else if(data[i]<=0.00-threshold)
				clipped[i]=data[i]+threshold;
			else
				clipped[i]=0;
	else
		return -1;
	
	*clippedData = clipped;
}
