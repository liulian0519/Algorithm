#include <stdio.h>
#include <math.h>
int main()
{
	int a[6][6],i,j,max,t,k;
	for(i=0;i<6;i++)
		for(j=0;j<6;j++)
			scanf("%d,",&a[i][j]);
	for(j=0;j<6;j++)
	{
		k=0;
		max=a[0][j]; 
		for(i=1;i<6;i++)
		{
			if(fabs(a[i][j])>max){
				max=a[i][j];
				k=i;				
			}
		}
		t=a[k][j];
		a[k][j]=a[k][k];
		a[k][k]=t;
		
    }
    for(i=0;i<6;i++)
    {
    	for(j=0;j<6;j++)
    	{
    		printf("%d ",a[i][j]);
			printf(" ");	
    	}
    	
    	printf("\n");
    }
}

