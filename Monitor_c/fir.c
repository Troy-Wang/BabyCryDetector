#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include "fir.h"

#define   pi         (3.1415926)

#define   Hamming    (1)

double sinc(double n)
{
	if(0==n) 
		return (double)1;
	else 
		return (double)(sin(pi*n)/(pi*n));
}

int Unit_Impulse_Response(int N,double w_c,int Win_Type,double *Output_Data)
{
	signed int Count = 0; 
	
	for(Count = -(N-1)/2;Count <= (N-1)/2;Count++)
	{
		*(Output_Data+Count+((N-1)/2)) = (w_c/pi)*sinc((w_c/pi)*(double)(Count));
	}	

	for(Count = -(N-1)/2;Count <= (N-1)/2;Count++)
	{
		*(Output_Data+Count+((N-1)/2)) *= (0.54 + 0.46 * cos((2*pi*Count)/(N-1)));
	} 
	
    
	return 1;
}


void Save_Input_Date (double Scand,int Depth,double *Input_Data)
{
	int Count;
	
	for(Count = 0 ; Count < Depth-1 ; Count++)
	{
		*(Input_Data + Count) = *(Input_Data + Count + 1);
	}
    
	*(Input_Data + Depth-1) = Scand;
}



double Real_Time_FIR_Filter(double *b,int b_Lenth,double *Input_Data)
{    
	int Count;
	double Output_Data = 0;
    
	Input_Data += b_Lenth - 1;  
    
	for(Count = 0; Count < b_Lenth ;Count++)
	{    	
		Output_Data += (*(b + Count)) *(*(Input_Data - Count)); 
	}         
 
	return (double)Output_Data;
}



void fir(double data[], int size,double *firData)
{
	int i;
	double w_p = 3*pi/4;
	double w_s = 7*pi/8;
	double w_c = (w_s + w_p)/2;
    
	int N = 0;  
	N = (int) ((11*pi)/(w_s - w_p) + 0.5);
	if(0 == N%2) N++;    
	
	double *Impulse_Response;        
	Impulse_Response = (double *) malloc(sizeof(double)*N);  
	memset(Impulse_Response,0,sizeof(double)*N);
	
	Unit_Impulse_Response(N,w_c,Hamming,Impulse_Response);
	
	double *Input_Buffer;
	double Output_Data = 0;
	Input_Buffer = (double *) malloc(sizeof(double)*N);  
	memset(Input_Buffer,0,sizeof(double)*N);
    
	for(i=0;i<size;i++)
	{   
		Save_Input_Date (data[i],N,Input_Buffer);
		firData[i] = Real_Time_FIR_Filter(Impulse_Response,N,Input_Buffer);
	}
	
	free(Impulse_Response);
	free(Input_Buffer);
}
