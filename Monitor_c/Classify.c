#include <stdio.h>
#include "Freq.h"
#include "absfft.h"
#include "clipping.h"
#include "enframe.h"
#include "max.h"
#include "mean.h"
#include "medfilt3.h"
#include "PitchFreq.h"
#include "smoothing.h"
#include "STE.h"
#include "ZCR.h"
#include "zcro.h"
#include <malloc.h>

int Classify(double data[], int size, int fs, int nBit)
{
	int score = 0;
	int stdPitchFreq = 20;  %5 frames
    	double stdAvgFreq = 1000;
	double stdSTE = 30;
	double stdAcc = 200;
	int stdZCR = 40;
    
	double feature_Freq,feature_ste,feature_steacc,feature_pf2;
	int feature_pf1;
	int feature_zcr;

	feature_Freq = Freq(data,size,fs,nBit);	
	printf("feature freq finished:%lf\n",feature_Freq);

	feature_Freq = Freq(data,size,fs,nBit);
	printf("feature freq finished:%lf\n",feature_Freq);

	STE(data,size,fs,nBit,&feature_ste,&feature_steacc);
	printf("feature ste finished: %lf\t%lf\n",feature_ste,feature_steacc);

	feature_zcr = ZCR(data,size,fs,nBit);
	printf("feature zcr finished:%d\n",feature_zcr);

	PitchFreq(data,size,fs,nBit,&feature_pf1,&feature_pf2);	
	printf("feature pf finished:%d\t%lf\n",feature_pf1,feature_pf2);

	if(feature_Freq > stdAvgFreq)
	{
		score = score + 2;
		printf("freq yes");
	}
    
	if(feature_PitchFreq > stdPitchFreq)
	{
		score = score + 5;
		printf("pitch freq yes");
	}

    
	if(feature_STE > stdSTE)
	{
		score = score + 1;
		printf("ste yes");
	}
    
	if(feature_STEAcc > stdAcc)
	{
		score = score + 1;
		printf("steacc yes");
	}
    
    	if(feature_ZCR > stdZCR)
	{
        	score = score + 1;
		printf("zcr yes");
	}
    
	printf("%d\n",score);
    
	if(score >= 5)
	{
		printf("baby cry!\n");
		return 1;
	}
	else
		return 0;
}
    

