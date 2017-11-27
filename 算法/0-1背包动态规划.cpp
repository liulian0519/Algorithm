#include<stdio.h>
int min(int a,int b)
{
	if(a<b) return a;
	else 
		return b;
}
int max(int a,int b)
{
	if(a<b) return b;
	else return a;
}
void knapsack(int v[],int w[],int c,int n,int m[][11])
{
	int i,j;
	int jmax=min(w[n]-1,c);
	for(j=0;j<=jmax;j++) m[n][j]=0;
	for(j=w[n];j<=c;j++) m[n][j]=v[n];
	
	for(i=n-1;i>1;i--)
	{
		jmax=min(w[i]-1,c);
		for(j=0;j<=jmax;j++) m[i][j]=m[i+1][j];
		for(j=w[i];j<=c;j++) m[i][j]=max(m[i+1][j],m[i+1][j-w[i]]+v[i]);
	}
	m[1][c]=m[2][c];	
	if(c>=w[1]) m[1][c]=max(m[1][c],m[2][c-w[1]]+v[1]);
}
void traceback(int m[][11],int w[],int c,int n,int x[])
{
	int i;
	for(i=1;i<n;i++)
	{
		if(m[i][c]==m[i+1][c])
		{
			x[i]=0;	
		} 
		else 
		{
			x[i]=1;
			c-=w[i];
		}	
	}
	
	x[n]=(m[n][c])?1:0;
}
int main()
{
	int n = 5,c=10;
	int w[]={0,2,2,6,5,4};
	int v[]={0,6,3,5,4,6};
	int x[n+1];
	int m[6][11];
	knapsack(v,w,c,n,m);
	printf("能带走的最大价值为：");
	printf("%d \n",m[1][c]); 
	printf("\n所带走物品的编号为（下标从1开始）：\n");
	traceback(m,w,c,n,x);
	for(int i=1; i<=n; i++)
	{
		if(x[i]==1)
		{
			printf("\n%d",i);
				
		}
	}
}
