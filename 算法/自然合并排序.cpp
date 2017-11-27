/*
��Ȼ�ϲ� 
*/ 
#include<stdio.h>
#define N 100

int Q;      //��Ȼ�ϲ�����������ɨ��ı����
int t[N];

void Merge(int c[],int d[],int l,int m,int r)
{
	//�ϲ�c[l:m]��c[m+1:r]��d[l:r]
	int i=l,j=m+1,k=r;
	while((i<=m)&&(j<=r))
	{
		if(c[i]<=c[j])
			d[l++]=c[i++];
		else
			d[l++]=c[j++];
	}
	if(i>m)						
		for(int q=j;q<=r;q++)		
			d[l++]=c[q];
	else
		for(int p=i;p<=m;p++)       
			d[l++]=c[p];
}

void PrintArray(int a[],int n)
{
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n"); 
}


void GetBPoint(int a[],int b[],int n,int &m)  //��¼�ָ������ 
{
	int j=0;
	b[j++]=0;
	for(int i=0;i<n-1;i++)
	{
		if(a[i+1]<a[i])
			b[j++]=i+1;
	}
	m=j;
//	PrintArray(b,j);
}

void MergePass(int x[],int y[],int s,int n)
{
	int i=0;
	while(i<=Q-2*s)   //n-2*s
	{
		int r=((i+2*s)<Q)?t[i+2*s]:n;  

		Merge(x,y,t[i],t[i+s]-1,r-1);
		i=i+2*s;
	}
	if(i+s<Q)
		Merge(x,y,t[i],t[i+s]-1,n-1);
	else
		if(i<Q)
		{
			for(int j=t[i];j<=n-1;j++)
				y[j]=x[j];
		}
}

void MergeSort(int a[],int n)
{
	int b[100];
	int s=1;
	while(s<Q)
	{
		MergePass(a,b,s,n);   //�ϲ�������b
		s+=s;
		MergePass(b,a,s,n);	//�ϲ�������a
		s+=s;
	}
}
int main()
{
	int n,i,a[100];
	printf("��������Ҫ��������ָ���:");
	scanf("%d",&n);
	printf("��������Ҫ���������:\n");
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);

	GetBPoint(a,t,n,Q);
	MergeSort(a,n);
	PrintArray(a,n);
	return 0;
}
