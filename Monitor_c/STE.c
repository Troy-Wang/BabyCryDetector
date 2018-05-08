#include "STE.h"
#include "max.h"
#include "mean.h"
#include <malloc.h>

void STE(double data[], int size, int fs, int nBit, double *feature_STE, double *feature_STEAcc)
{
	int i,k;
	int max_pos;
	double maxEnergy, threshold;
	double secPerFra = 20*0.001;
	int frameLength = secPerFra*fs;
	int frameInc = frameLength;
	double **frames;
	double *energy; 
	double *energyDiff;
	int frameNum;	
	double energySum = 0;
	double energyBiggerNum = 0;

	enframe(data, size, frameLength, frameInc, &frames, &frameNum);
	energy =(double *)malloc(frameNum*sizeof(double));
	energyDiff =(double *)malloc(frameNum*sizeof(double));

	for(i=0; i<frameNum; i++)
	{
		energy[i] = 0;
		for(k=0; k<frameLength; k++)
			energy[i] += frames[i][k]*frames[i][k];
	}			

	maxEnergy = max(energy,frameNum,1,-1,&max_pos);
	threshold = 0.2*maxEnergy;

	for(i=0; i<frameNum; i++)
	{
		if (energy[i]>threshold)
		{
			energySum += energy[i];
			energyBiggerNum++;
		}
	}

	*feature_STE = energySum/energyBiggerNum;

	for(i=0; i<frameNum-1; i++)
		energyDiff[i] = energy[i+1]-energy[i];
	energyDiff[frameNum-1] = 0;

	*feature_STEAcc = max(energyDiff,frameNum,1,-1,&max_pos);

	free(energy);
	free(energyDiff);
}
