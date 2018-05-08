#include "PitchFreq.h"
#include "max.h"
#include "smoothing.h"
#include "clipping.h"
#include "enframe.h"
#include <malloc.h>

void PitchFreq(double data[], int size, int fs, int nBit, int *feature_PitchFreq, double *feature_PitchFreq2)
{
	int i,j,k,m,n;

	double secPerFra = 30*0.001;
	int frameLength = secPerFra*fs;
	int frameInc = frameLength/3;
	int frameNum;
	int cutting;
	int Rmax_pos;
	int feature1=0;
	double *firData, *clippedData;
	double frameSTE, Rmax;
	double **frames;
	double *Rm;
	double *PitchFreq, *smoothedPitchFreq;
	int feature_PitchFreq2_count =0;
	*feature_PitchFreq2=0;

	Rm = (double *)malloc(sizeof(double)*frameLength);
	//firData = (double *)malloc(sizeof(double)*size);
	clippedData = (double *)malloc(sizeof(double)*size);

	//fir(data,firData);
	clipping(data,size,1,&clippedData);	
	
	enframe(clippedData, size, frameLength, frameInc, &frames, &frameNum);
	PitchFreq = (double *)malloc(sizeof(double)*frameNum);
	smoothedPitchFreq = (double *)malloc(sizeof(double)*frameNum);
	
	cutting = (int)(0.003*fs);	

	for(i=0;i<frameNum;i++)
	{
		frameSTE = 0;
		for(j=0;j<frameLength;j++)
			frameSTE += frames[i][j]*frames[i][j];	
		for(k=0;k<frameLength;k++)
		{
			Rm[k]=0;
			for(m=k+1;m<frameLength;m++)
				Rm[k] = Rm[k]+frames[i][m]*frames[i][m-k];
		}
		Rmax = max(Rm,frameLength,cutting,-1,&Rmax_pos);	
		if(Rmax<=0.25*frameSTE || Rmax==0)
			PitchFreq[i]=0;
		else
		{
			PitchFreq[i]=fs/(Rmax_pos+1);
		}
	}	

	smoothing(PitchFreq,frameNum,&smoothedPitchFreq);
	
	for(n=0;n<frameNum;n++)
	{
		if(smoothedPitchFreq[n]>200.00)
			feature1++;
		if(smoothedPitchFreq[n]>0)
			feature_PitchFreq2_count++;
	}
	*feature_PitchFreq = feature1;
	*feature_PitchFreq2 = (double)feature1/feature_PitchFreq2_count;

	free(Rm);
	free(clippedData);
	free(PitchFreq);
	free(smoothedPitchFreq);
}
