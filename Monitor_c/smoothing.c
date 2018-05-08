#include "smoothing.h"
#include "medfilt3.h"

void smoothing(double data[], int size, double **smoothedData)
{
	medfilt3(data,size,&(*smoothedData));
}	
