#include "zcro.h"
#include "mean.h"
#include "enframe.h"

int ZCR(double data[], int size, int fs, int nBit)
{
	int i;
	double num = 0, sum =0;
	double secPerFra = 20*0.001;	
	int frameLength = secPerFra*fs;	//frame length
	int frameInc = frameLength/2;	//frame increment
	double **frames;
	int frameNum;
	double *zcr;
	double feature_ZCR;

	enframe(data,size,frameLength,frameInc,&frames,&frameNum);

	zcro(frames,frameNum,frameLength,&zcr);
	

	for(i=0;i<frameNum;i++)
		if(zcr[i]>0)
		{
			sum += zcr[i];
			num = num + 1 ;
		}

	feature_ZCR = sum/num;

	return feature_ZCR;
}
