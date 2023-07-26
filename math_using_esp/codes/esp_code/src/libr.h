double **linalg_sub(double **a, double **b, int m, int n);
double **block(double **a,double **b,double **c,int m,int n);
double linalg_norm(double **a, int m);
void swap(double **a,int row1,int row2,int col);
int rank(double **a,int m);
double **matmul(double **a, double **b, int r1, int c1, int c2);
double **transpose(double **a,  int m, int n);
double linalg_norm(double **a, int m);


double **createMat(int m,int n)
{
 int i;
 double **a;
 
 //Allocate memory to the pointer
a = (double **)malloc(m * sizeof( *a));
    for (i=0; i<m; i++)
         a[i] = (double *)malloc(n * sizeof( *a[i]));

 return a;
}


double linalg_norm(double **a, int m)
{
int i;
double norm=0.0;

 for(i=0;i<m;i++)
 {
norm = norm + a[i][0]*a[i][0];
}
return norm;

}


 

double **transpose(double **a,  int m, int n)
{
int i, j;
double **c;
//printf("I am here");
c = createMat(n,m);

 for(i=0;i<n;i++)
 {
  for(j=0;j<m;j++)
  {
c[i][j]= a[j][i];
//  printf("%lf ",c[i][j]);
  }
 }
return c;
}



double **linalg_sub(double **a, double **b, int m, int n)
{
int i, j;
double **c;
c = createMat(m,n);

 for(i=0;i<m;i++)
 {
  for(j=0;j<n;j++)
  {
c[i][j]= a[i][j]-b[i][j];
  }
 }
return c;

}


double **block(double **a,double **b,double **c,int m,int n)
{
 double **l;
 int i,j,k=0;

 l=createMat(m,m);
 for(i=0;i<m;i++)
 {
  for(j=0;j<n;j++)
  {
    l[i][k]=a[i][j];
  }
 }
  k+=1;
	
 for(i=0;i<m;i++)
 {
  for(j=0;j<n;j++)
  {
   l[i][k]=b[i][j];
  }
 }
  k+=1;

 for(i=0;i<m;i++)
 {
  for(j=0;j<n;j++)
  {
	l[i][k]=c[i][j];
  }
 }

 return l;
}

int rank(double **a,int m)
{
  int ra=m,row,col,i;
  double b;
	

  for(int row=0;row<ra;row++)
  {
   if(a[row][row])
   {
    for(int col=0;col<m;col++)
    {
     if(col!=row)
     {				
	 b=a[col][row]/a[row][row];
         for(i=0;i<ra;i++)			     a[col][i]-=b*a[row][i];
				}}}
     else
     {
	int reduce=1;
	for(i=row+1;i<m;i++)
	{
	 if(a[i][row])
	 {
	    swap(a,row,i,ra);
	    reduce=0;
	    break;
	 }}
      if(reduce)
      {
	ra-=1;
	for(i=0;i<m;i++)
	{		
	  a[i][row]=a[i][ra];
	}}
	row-=1;		
	}
      }
	return ra;
}

void swap(double **a,int row1,int row2,int col)
{
	int i,temp;
	for(i=0;i<col;i++)
	{
	    temp=a[row1][i];
	    a[row1][i]=a[row2][i];
	    a[row2][i]=temp;
	}
}

					


double **mat_mul(double **a, double **b, int r1,int c1, int c2)
{
int i, j, k;
double **c; 
c = createMat(r1,c2);                                                            
for(i=0;i<r1;i++)
{
	for(j=0;j<c2;j++)
	{
		c[i][j]=0;
	}
}
for(i=0;i<r1;i++)
{
	for(j=0;j<c2;j++)
	{
		for(k=0;k<c1;k++)
		{
			c[i][j]+=a[i][k]*b[k][j];
		}
	}
}
return c;
}



double **load_ser(AsyncWebServerRequest *request,const char* matrix1[3])
{
	double **a;
	int m=3,n=1;
	a = createMat(m,n);
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			a[i][j]=request->getParam(matrix1[i])->value().toDouble();
		}
	}
	return a;
}

