#include<stdio.h>
int a[100][100];
int n;
int b[100][100];   //�洢�ظ����� ��ֵ 
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
	if(b[r][j]!=-1)			//�˾���˼Ϊû���ظ�ֵ��˵��ֻ��һ�� 
		return b[r][j];
	b[r][j]=max(maxsum(r+1,j),maxsum(r+1,j+1)) + a[r][j];
	return b[r][j];
}

int main()
{
	int i,j,Msum;
	printf("��������Щ���ֹ��м��У�\n");
	scanf("%d",&n);
	printf("��������Щ���֣�\n");
	for(i=0;i<n;i++)
		for(j=0;j<=i;j++)
		{
			scanf("%d",&a[i][j]);
			b[i][j]=-1;
		}
	

	printf("���ֵΪ��%d",maxsum(0,0));
} 
