//#include<stdio.h>
//#include<string.h>
//int main()
//{
//    char A[600];
//    int i=0,s,k;
//    printf("please chose a number:\n");
//    scanf("%s",A);
//    printf("please chose the times:");
//    scanf("%d",&s);
//    while(s>0)
//    {i=0;
//             
//    while(i<strlen(A)&&A[i]<A[i+1])i++;
//    for(k=i;k<strlen(A);k++)
//        {
//        A[k]=A[k+1];
//        }
//    s--;
//    }
//    printf("%s",A);
// 
//}
#include<stdio.h>
#include<string.h>
int main(){
	char a[600];
	int i=0;
	int s,k;
	printf("please input a number:\n");
	scanf("%s",a);
	printf("please input times:");
	scanf("%d",&s);
	while(s>0){
		i=0;
		while(i<strlen(a)&&a[i]<a[i+1])
			i++;
		for(k=i;k<strlen(a);k++){
			a[k]=a[k+1];
		}
		s--;
	}
	printf("%s",a);
}
