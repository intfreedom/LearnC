#include<stdio.h>
#define N 14
int main()
{
	int i,j,k,n=0,a[N][N];
	while(n<=0||n>=13){
		printf("Please input the line: ");
		scanf("%d", &n);
	}

	printf("%d line YangHui is: \n",n);
	for(i=1;i<=n;i++)
	{
		a[i][1]=a[i][i]=1;
	}
	for(i=3;i<=n;i++)
		for(j=2;j<=i-1;j++)
			a[i][j]=a[i-1][j-1]+a[i-1][j];
	for(i=1;i<=n;i++){
		for(k=1;k<=n-i;k++)
			printf("   ");//three space
		for(j=1;j<=i;j++)
			printf("%6d",a[i][j]);

		printf("\n");
	}

	printf("\n");

	return 0;

}


//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#define BLUE 'B'
//#define WHITE 'W'
//#define RED 'R'
//#define swap(x,y){char temp;\
//	temp=color[x];\
//	color[x]=color[y];\
//	color[y]=temp;}
//
//int main()
//{
//
//	char color[] = {'R','W','W','W','R','R','R','B','B','\0'};
//	int b=0;
//	int w=0;
//	int r=strlen(color)-1;
//	int i;
//
//	for(i=0;i<strlen(color);i++)
//	{
//		printf("%c",color[i]);
//	}
//	printf("\n");
//
//	while(w<=r)
//	{
//		if(color[w]==WHITE)
//			w++;
//		else
//		{
//			if(color[w]==BLUE)
//			{
//				swap(b,w);
//				b++;
//				w++;
//			}
//			else
//			{
//				while(w<r&&color[r]==RED)
//					r--;
//				swap(r,w);
//					r--;
//			}
//		}
//	}
//	for(i=0;i<strlen(color);i++)
//		printf("%c",color[i]);
//	printf("\n");
//	return 0;
//}