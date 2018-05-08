#include "enframe.h"
#include <malloc.h>

void enframe(double data[], int size, int frameLength, int frameInc,double ***frames,int *frameNum)
{
	int i,j;
	*frameNum = (int)((size-frameLength+frameInc)/frameInc);	
	double **framesTemp = (double **)malloc(sizeof(double)*(*frameNum));
	
	for(i=0;i<(*frameNum);i++)
	{
		framesTemp[i] = (double *)malloc(sizeof(double)*frameLength);
		for(j=0;j<frameLength;j++)
			framesTemp[i][j] = data[i*frameInc+j];
	}			
	*frames = framesTemp;
}
