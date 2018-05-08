#include <stdio.h>
#include "enframe.h"

int main()
{
	int i,j;
	double data[] = {1,2,3,4,5,6};
	int frameLength = 3;
	int frameInc =2;
	double **frames = NULL;
	int frameNum;

	enframe(data,sizeof(data)/sizeof(double),frameLength,frameInc,&frames,&frameNum);

	printf("%d\n",frameNum);
	for(i=0;i<frameNum;i++)
	{
		for(j=0;j<frameLength;j++)
			printf("%lf\t",frames[i][j]);	
		printf("\n");
	}
	return 1;
}
