#include<stdio.h>
#define n 8
main()
{
	int i,j,y[n][n];
	for(i=0;i<n;i++)
	{
		y[i][0]=1;
		y[i][i]=1;
	}
	for(i=0;i<n;i++)
	{
		for(j=1;j<i;j++)
		  y[i][j]=y[i-1][j]+y[i-1][j-1];
		for(j=0;j<=i;j++)
		  printf("%5d",y[i][j]); 
		printf("\n");
	}
}
