#include<stdio.h>
int a[100][100];
int n;
int b[100][100];   //存储重复计算 的值 
int max(int a,int b)
{
	if(a>b) return a;
	else 
		return b;
}
int maxsum(int r,int j)
{
//	
//	if(r==n)
//	return a[r][j];
//	else
//	{
//		return max(maxsum(r+1,j),maxsum(r+1,j+1)) + a[r][j];
//	}
	if(b[r][j]!=-1)			//此句意思为没有重复值，说明只有一行 
		return b[r][j];
	b[r][j]=max(maxsum(r+1,j),maxsum(r+1,j+1)) + a[r][j];
	return b[r][j];
}

int main()
{
	int i,j,Msum;
	printf("请输入这些数字共有几行：\n");
	scanf("%d",&n);
	printf("请输入这些数字：\n");
	for(i=0;i<n;i++)
		for(j=0;j<=i;j++)
		{
			scanf("%d",&a[i][j]);
			b[i][j]=-1;
		}
	

	printf("最大值为：%d",maxsum(0,0));
} 
