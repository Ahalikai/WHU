#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <iostream.h>
#include <fstream.h>

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)


#define ITERS 100 //��������
#define T 100
#define T_min 1e-8 
#define delta 0.98

long  rnd_uni_init;                 /* serves as a seed for rnd_uni()   */
int   seed; 


double x[ITERS];   //x
double f[ITERS];   // y
double minf;     //�������ҵ�����Сyֵ
double minx;    //�������ҵ�����Сy��Ӧ��xֵ

////////////////////////////

double rnd_uni(long *idum); //����0��1֮��������
double rand_double(double l, double u); //����[l, u]�������
double F(double x);
void InitSA();
double SA();

////////////////////////////


void main()
{
	srand((unsigned)time(NULL));
	do{seed=rand();}while(seed==0);
	rnd_uni_init = -(long)seed;  //��ʼ�����������

    InitSA();  //��ʼ��
	minf = SA(); //ִ��ģ���˻��㷨

    cout<<"Min value = "<<minf<<"	Min X = "<<minx<<endl;
}

// ���� y = (x-1)*(x-1)����Сֵ
// 2(x-1)=0  ==> x= 1   y =0
double F(double x){
	double value = (x-1)*(x-1);
    return value;
}

void InitSA(){
	for(int i = 0; i < ITERS; i++){
        x[i] = rand_double(-2, 4);  // ������[-2, 4]���������һ����
		f[i] = F(x[i]);
    }
	minf=f[0];
	minx = x[0];
	for(i = 1; i < ITERS; i++){
		if(f[i] < minf){
			minf = f[i];
			minx = x[i];
		}
	}
	cout<<"��ʼ Min value = "<<minf<<"	min X = "<<minx<<endl;
}

double SA(){
	int count=0; // for print
    double t = T;
    while (t > T_min){
        for(int i = 0; i < ITERS; i++){ 
			//����x[i]�� ����һ���µĽ�temp_x
            double f_old = f[i];
            double temp_x = x[i] + rand_double(0,1)*t;  // ����һ���µĽ⣬��������
			//Խ���� [-2, 4]
            if(temp_x >= -2 && temp_x <= 4){
                double f_new = F(temp_x);
                if(f_new < f_old){
                    x[i] = temp_x;
					f[i] = f_new;
				}
                else{
                    double p = exp((f_new - f_old) / t);  //������ܸ���p
                    if(p > rand_double(0,1)){
                        x[i] = temp_x;
						f[i] = f_new;
					}
                }
				//�����ҵ����ֵ
				if(f[i] < minf){
					minf = f[i];
					minx = x[i];
				}
            }//end-if-Խ��
        }//end-for
        t = t * delta;   //���´���  delta=0.98

		count++; //for print
		if(count%100==0)
			cout<<"Min value = "<<minf<<"	Min X = "<<minx<<endl;
    }//end-while
    return minf;
}


double rand_double(double l, double u){
	double r;
	r = l+(u-l)*rnd_uni(&rnd_uni_init);
	return r;
}

double rnd_uni(long *idum){
  long j;
  long k;
  static long idum2=123456789;
  static long iy=0;
  static long iv[NTAB];
  double temp;

  if (*idum <= 0)
  {
    if (-(*idum) < 1) *idum=1;
    else *idum = -(*idum);
    idum2=(*idum);
    for (j=NTAB+7;j>=0;j--)
    {
      k=(*idum)/IQ1;
      *idum=IA1*(*idum-k*IQ1)-k*IR1;
      if (*idum < 0) *idum += IM1;
      if (j < NTAB) iv[j] = *idum;
    }
    iy=iv[0];
  }
  k=(*idum)/IQ1;
  *idum=IA1*(*idum-k*IQ1)-k*IR1;
  if (*idum < 0) *idum += IM1;
  k=idum2/IQ2;
  idum2=IA2*(idum2-k*IQ2)-k*IR2;
  if (idum2 < 0) idum2 += IM2;
  j=iy/NDIV;
  iy=iv[j]-idum2;
  iv[j] = *idum;
  if (iy < 1) iy += IMM1;
  if ((temp=AM*iy) > RNMX) return RNMX;
  else return temp;
}

