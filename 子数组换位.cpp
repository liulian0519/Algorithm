#include<stdio.h>
void swap(int a[],int low,int high)
{
	int temp,i;
	while(low<high)
	{
		temp=a[low];
		a[low]=a[high];
		a[high]=temp;
		low++;
		high--;
	} 
}

int main(){
	int a[100],i,k,n;
	printf("��������Ҫ��λ�������Ԫ�ظ���\n");
	scanf("%d",&n);
	printf("��������л�λ������\n");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("��������Ҫ��λ���±�k\n");
	scanf("%d",&k);
	swap(a,0,k-1);
	swap(a,k,n-1);
	swap(a,0,n-1);
	for(int i=0;i<n;i++)
		printf("%d  ",a[i]);
	return 0;
}


