#include <stdio.h>
int main ()
{
	int r,c;
	for(r=1;r<10;r++)
		{
			for(c=1;c<r+1;c++)
				printf("%5d",r*c);
			printf("\n"); 
		}
} 
