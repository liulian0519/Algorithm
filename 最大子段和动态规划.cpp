#include<stdio.h>
int maxsum(int n,int *a)
{
	int sum = 0,b=0,i;
	for(i=0;i<n;i++)
	{
		if(b>0) b+=a[i];
		else
		b=a[i];
		if(b>sum) sum = b;
	}
	return sum;
}
int main()
{
	int i, n,result,a[100];
	FILE *fp1,*fp2;
	fp1=fopen("子段和in.txt","r");
	fp2=fopen("子段和out.txt","w");
	if(fp1==NULL||fp2==NULL)
	{
		printf("文件无法打开，可能不存在");
		return 0;
	}
	fscanf(fp1,"%d",&n);
	for(i=0;i<n;i++)
	{
		fscanf(fp1,"%d",&a[i]);
	}
	result = maxsum(n,a);
	fprintf(fp2,"%d",result);
	printf("计算成功，请前往文件中查询");
}
