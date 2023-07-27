#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"libr.h"
int main()
{
	double **A,**B,**C,**k,**d,**e,**one,**f;
	double m=3,n=1,s,two;
	A=loadtxt("A.dat",3,1);
	B=loadtxt("B.dat",3,1);
	C=loadtxt("C.dat",3,1);
	d=linalg_sub(B,A,m,n);
	e=linalg_sub(C,B,m,n);
	k=block(A,B,C,m,n);
	int o;
	o=rank(k,m);
	if(o<3)
		printf("Points are collinear\n");
        else
		
		printf("Points are not collinear\n");
	f=transpose(e,m,n);
	one=mat_mul(f,d,n,m,n);
	two=linalg_norm(e,m);
	s=one[0][0]/two;
	printf("B divides AC in the ratio %lf\n",s);
	save(s);

}

