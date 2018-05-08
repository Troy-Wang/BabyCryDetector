#include <math.h>
#include <malloc.h>

/*定义复数类型*/
typedef struct
{
	double real;
	double img;
}complex;

void fft(complex *, complex *, int);
void initW(complex *,int);
void change(); /*变址*/
void add(complex ,complex ,complex *); /*复数加法*/
void mul(complex ,complex ,complex *); /*复数乘法*/
void sub(complex ,complex ,complex *); /*复数减法*/

void absfft(double data[], int size, double **absfftRes, int *resSize)
{
	int i; 
	int N=(int)pow(2,ceil(log(size)/log(2)));
	complex *x = (complex *)malloc(sizeof(complex)*N);
	complex *W = (complex *)malloc(sizeof(complex)*N);
	double *absfftResTemp = (double *)malloc(sizeof(double)*N);
	*resSize = N;
	
	for(i=0;i<size;i++)
	{
		x[i].real = data[i]; 
		x[i].img = 0;
	/*
		if(i%2==0)
		{
			x[i].real = i+1;
			x[i].img = 0;
		}
		else
		{
			x[i].real = 0;
			x[i].img = i+1;
		}
	*/
	}
	if(size<N)
	{
		for(i=size;i<N;i++)
		{
			x[i].real = 0;
			x[i].img = 0;
		}
	}
	initW(W,N);
	fft(x,W,N);
	
	*absfftRes = absfftResTemp;	
}

/*快速傅里叶变换*/
void fft(complex *x, complex *W, int N)
{
	int i=0,j=0,k=0,l=0;
	complex up,down,product;
	change(x,N);
		printf("before change");
	for(i=0;i< log(N)/log(2) ;i++)
	{   /*一级蝶形运算*/
		l=1<<i;
		for(j=0;j<N;j+= 2*l )
		{             /*一组蝶形运算*/
			for(k=0;k<l;k++)
			{        /*一个蝶形运算*/
				mul(x[j+k+l],W[N*k/2/l],&product);
				add(x[j+k],product,&up);
				sub(x[j+k],product,&down);
				x[j+k]=up;
				x[j+k+l]=down;
			}
		}
	}
}

/*初始化变换核*/
void initW(complex *W,int N)
{
	double PI = atan(1)*4;
	int i;
	for(i=0;i<N;i++)
	{
		W[i].real=cos(2*PI/N*i);
		W[i].img=-1*sin(2*PI/N*i);
	}
}

/*变址计算，将x(n)码位倒置*/
void change(complex *x, int N)
{
	complex temp;
	unsigned short i=0,j=0,k=0;
	double t;
	for(i=0;i<N;i++)
	{
 		k=i;j=0;
 		t=(log(N)/log(2));
		while( (t--)>0 )
		{
			j=j<<1;
			j|=(k & 1);
			k=k>>1;
   		}
		if(j>i)
		{
			temp=x[i];
			x[i]=x[j];
			x[j]=temp;
		}
	}
}


void add(complex a,complex b,complex *c)
{
	c->real=a.real+b.real;
	c->img=a.img+b.img;
}

void mul(complex a,complex b,complex *c)
{
	c->real=a.real*b.real - a.img*b.img;
	c->img=a.real*b.img + a.img*b.real;
}

void sub(complex a,complex b,complex *c)
{
	c->real=a.real-b.real;
	c->img=a.img-b.img;
}
