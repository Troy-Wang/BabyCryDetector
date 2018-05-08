#include "max.h"

double max(double *data, int size, int start, int end, int *max_pos)
{
	int i;
	double maximum = data[start-1];
	*max_pos = start;	

	if(end==-1)
		end = size;
	if(end<start)
	{
		return -1;
		*max_pos = -1;
	}

	for(i=start-1; i<end; i++)
		if(maximum<data[i])
		{
			maximum = data[i];
			*max_pos = i+1;
		}

	return maximum;
}
