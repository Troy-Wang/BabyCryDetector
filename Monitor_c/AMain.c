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
#include "Classify.h"
#include <malloc.h>

int main()
{
	double data[970443];
	int i=0;
	int size = 970443;
	double temp;
	int isBabyCry;
	FILE *fp;
	fp = fopen("data1.txt","r");

	while( fscanf(fp,"%lf",&temp)!=EOF)
	{
		data[i] = temp;
		i++;
	}
	printf("get data finished:%d\n",i);
	
	isBabyCry = Classify(data,size,44100,8);

	if(isBabyCry == 1)
		printf("baby cry\n");
	else
		printf("not baby cry\n");

	
}
