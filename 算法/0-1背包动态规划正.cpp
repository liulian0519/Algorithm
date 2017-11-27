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
void knapsack(int v[],int w[],int c,int n,int m[][10])
{
	int i,j;
	
	for(j=0;j<w[i];j++) m[1][j]=0;
	for(j=w[1];j<=c;j++) m[1][j]=v[1];
	for(i=2;i<=n-1;i++)
	{
		for(j=0;j<w[i];j++) m[i][j]=m[i-1][j];
		for(j=w[i];j<=c;j++) m[i][j]=max(m[i-1][j],m[i-1][j-w[i]]+v[i]);
	}
	m[n][c]=m[n-1][c];
	if(c>=w[n]) m[n][c]=max(m[n][c],m[n-1][c-w[n]]+v[n]);
}
void traceback(int m[][10],int w[],int c,int n,int x[])
{
	int i;
	for(i=n;i>1;i--)
	{
		if(m[i][c]==m[i-1][c])
		{
			x[i]=0;	
		} 
		else 
		{
			x[i]=1;
			c-=w[i];
		}	
	}
	
	x[1]=(m[1][c])?1:0;
}
int main()
{
	int n = 5,c=10;
	int w[]={0,2,2,6,5,4};
	int v[]={0,6,3,5,4,6};

	int x[n+1];
	int m[10][10];
	knapsack(v,w,c,n,m);
	printf("能带走的最大价值为：");
	printf("%d ",m[n][c]); 
	printf("\n所带走物品的编号为（下标从1开始）：\n");
	traceback(m,w,c,n,x);
	for(int i=1; i<=n; i++)
	{
		if(x[i]==1)
		{
			printf("%d ",i);
		}
	}

	
}
