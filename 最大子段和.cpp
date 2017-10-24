/*
最大子段和 
文件中第一行代表该数组的大小 
*/
#include<stdio.h>
/*分治法  时间复杂度为nlogn*/
int max(int a[],int left,int right) 
{
	int result=0;
	int leftsum,rightsum,i,j;
	if(left==right)
	{
		if(a[left]>0) result=a[left];
		else	result=0;
			
	}
	else
	{
		int mid=(left+right)/2;
		leftsum=max(a,left,mid);
		rightsum=max(a,mid+1,right);
		int s1=0,lefts=0;
		for(i=mid;i>=left;i--)
		{
			lefts+=a[i];
			if(lefts>s1) s1=lefts;
		} 
		int s2=0,rights=0;
		for(j=mid+1;j<=right;j++)
		{
			rights+=a[j];
			if(rights>s2) s2=rights;
		}
		result=s1+s2;
		if(result<leftsum) result=leftsum;
		if(result<rightsum) result=rightsum;
		
	}
	return result;
}



 
/*平常方法 结果正确*/ 
//int max(int a[],int n)
//{
//	int i,j,sum=0;
//	int summax=a[0];
//	for(i=0;i<n;i++)
//	{
//		sum = 0;
//		for(j=i;j<n;j++)
//		{
//			sum+=a[j];
//			if(sum>summax)
//			summax=sum;
//		}
//	}
//	return summax;
//}
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
//scanf("%d",&n);
//	for(i=0;i<n;i++)
//	scanf("%d",&a[i]);
//
	result=max(a,0,n-1);
//	printf("%d",result);
	fprintf(fp2,"%d",result);
	printf("计算成功，请前往文件中查询");

}
