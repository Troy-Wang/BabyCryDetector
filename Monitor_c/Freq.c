#include "Freq.h"
#include "absfft.h"
#include "max.h"
#include "smoothing.h"
#include <malloc.h>
#include <stdio.h>

double Freq(double data[], int size, int fs, int nBit)
{
	int i,j;
	double *xfft,*Fx,*smoothedfft;
	int xfftSize, cutting=0, max_pos;
	double df,maxfft,threshold;
	double sum1=0, sum2=0;
	double feature_Freq;

	absfft(data,size,&xfft,&xfftSize);	
	xfft[0] = 0;
	printf("after absfft: %lf\n",xfft[10]);

	smoothing(xfft,xfftSize,&smoothedfft);

	maxfft = max(smoothedfft,xfftSize,1,-1,&max_pos);
	threshold = 0.25*maxfft;

	df = (double)fs/xfftSize;
	Fx = (double *)malloc(xfftSize*sizeof(double));
	for(i=0;i<xfftSize;i++)
	{
		Fx[i] = df*i;
		if(cutting == 0 && Fx[i]>=6000)
			cutting = i;
	} 

	if(cutting ==0)
		cutting = xfftSize;

	for(j=0;j<cutting;j++)
	{
		if(smoothedfft[j]>threshold)
		{
			sum1 += Fx[j]*smoothedfft[j];
			sum2 += smoothedfft[j];
		}
	}
	
	feature_Freq = sum1/sum2;

	free(Fx);			
	
	return feature_Freq;
}
