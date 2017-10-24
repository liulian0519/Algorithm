//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//void lcslength(int m,int n,char *x,char *y,int **c ,int **b)
//{
//	int i,j;
//	for(i=1;i<=m;i++) c[i][j]=0;
//	for(i=1;i<=n;i++) c[0][j]=0;
//	for(i=1;i<=m;i++)
//		for(j=1;j<=n;j++)
//		{
//			if(x[i]==y[i])
//			{
//				c[i][j]=c[i-1][j-1]+1;
//				b[i][j]=1;
//			}
//			else if(c[i-1][j]>=c[i][j-1])	
//			{
//				c[i][j]=c[i-1][j];
//				b[i][j]=2;
//			}
//			else
//			{
//				c[i][j]=c[i][j-1];
//				b[i][j]=3;
//			}
//		}
//}
//void lcs(int i,int j,char *x,int **b)
//{
//	if(i==0||j==0) return;
//	if(b[i][j]==1)
//	{
//		lcs(i-1,j-1,x,b);
//		printf("%c",x[i]);
//	}
//	else if(b[i][j]==2)
//	lcs(i-1,j,x,b);
//	else
//	lcs(i,j-1,x,b);
//}
//int main()
//{
//	char *x,*y;
//	int i;
//	int **c;
//	int **b;
//	int m,n;
//	printf("�������ַ���x�ĳ��ȣ�\n");
//	scanf("%d",&m);
//	printf("�������ַ���x�� ");
//	scanf("%s",x);
//	printf("�������ַ���Y�ĳ��ȣ�\n");
//	scanf("%d",&n);
//	printf("�������ַ���Y�� ");
//	scanf("%s",y);
//	lcslength(m,n,x,y,c,b);
//	lcs(m,n,x,b);
//}
#include<stdio.h>
#include<string.h>
int c[200][200];   //��c[i][j]��¼X[i]��Y[j] ��LCS �ĳ���
int b[200][200];   //b[i][j]��¼c[i][j]��ͨ����һ���������ֵ��õģ��Ծ��������ķ���
char f[200];


/*ȡc[i-1][j]��c[i][j-1]�����ֵ,����¼c[i][j]��ͨ����һ���������ֵ��õģ��Ծ��������ķ���*/
int Max(int m,int n,int i,int j)
{
	if(m > n)
	{
		b[i][j] = -1;
		return m;
	}
	else
	{
		b[i][j] = 1;
		return n;
	}
}

/*�ݹ��ӡLCS��Ԫ������*/
void print(int i,int j,int s,char x[],char y[])
{
	if(b[i][j] == 0)
	{
		f[s-1] = x[i-1];
		i--;j--;s--;
		print(i,j,s,x,y);
	}
	else if(b[i][j] == -1)
	{
		i--;
		print(i,j,s,x,y);
	}
	else if(b[i][j] == 1)
	{
		j--;
		print(i,j,s,x,y);
	}
}

int LCS(char x[],char y[])
{
	int i,j;
	int x_len,y_len;
	x_len = strlen(x);
	y_len = strlen(y);
	printf("   ");
	for(i = 0;i < y_len;i++)
	{
		printf("%c  ",y[i]);
	}
	printf("\n");
	for(i = 1;i <= x_len;i++)
	{
		printf("%c  ",x[i-1]);
		for(j = 1;j <= y_len;j++)
		{
			if(x[i-1] == y[j-1])
			{
				c[i][j] = c[i-1][j-1] +1;
				b[i][j] = 0;
				printf("%d  ",c[i][j]);
			}
			else
			{
				c[i][j] = Max(c[i-1][j],c[i][j-1],i,j);
				printf("%d  ",c[i][j]);
			}
		}
		printf("\n");
	}

	//��ӡX��Y��LCS
	printf("X��Y��LCS��:");
	print(x_len,y_len,c[x_len][y_len],x,y);
	printf("%s",f);
	printf("\n");
	return c[x_len][y_len];
}

int  main()
{
	char X[200],Y[200];
	int i,j,s;
	printf("�������ַ���X:");
	scanf("%s",X);
	printf("�������ַ���Y:");
	scanf("%s",Y);
	s = LCS(X,Y);
	printf("X��Y��LCS: %d \n",s);
}
