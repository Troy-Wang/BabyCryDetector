#include "zcro.h"
#include <malloc.h>

void zcro(double **frames, int frameNum, int frameLength, double **zcr)
{
	int i,k;
	double *zcrTemp = (double *)malloc(sizeof(double)*frameNum);

	for(i=0; i<frameNum; i++)
		for(k=0; k<frameLength-1; k++)
			if(frames[i][k]*frames[i][k+1]<0)
				zcrTemp[i]++;
	*zcr = zcrTemp;
}	
