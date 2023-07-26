double **createMat(int m,int n);
double **loadtxt(char *str,int m,int n);
void print(double **p,int m,int n);
double **linalg_sub(double **a, double **b, int m, int n);
double **block(double **a,double **b,double **c,int m,int n);
double linalg_norm(double **a, int m);
void swap(double **a,int row1,int row2,int col);
int rank(double **a,int m);
void printlone(int o);
double **matmul(double **a, double **b, int r1, int c1, int c2);
double **transpose(double **a,  int m, int n);
double linalg_norm(double **a, int m);
void save(double a);



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

double **loadtxt(char *str,int m,int n)
{
FILE *fp;
double **a;
int i,j;


a = createMat(m,n);
fp = fopen(str, "r");

 for(i=0;i<m;i++)
 {
  for(j=0;j<n;j++)
  {
   fscanf(fp,"%lf",&a[i][j]);
  }
 }
//End function for reading matrix from file

fclose(fp);
 return a;

}


void print(double **p, int m,int n)
{
 int i,j;

 for(i=0;i<m;i++)
 {
  for(j=0;j<n;j++)
  printf("%lf ",p[i][j]);
 printf("\n");
 }
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

void printlone(int o)
{
	printf("%d",o);
	printf("\n");
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


void save(double a) {
  FILE *fp;
  fp = fopen("result.dat", "w");
  fprintf(fp, "%lf", a);
  fprintf(fp, "\n");
  fclose(fp);
}
