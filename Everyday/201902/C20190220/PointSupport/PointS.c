#include<stdio.h>

int main()
{
	int i=11;
	int* pl;
	char* pc;
	float* pf;

	pl = &i;

	*((int*)0X61FF28) = 100;

	printf("%#X\n",pl);
	printf("%d\n",i);
}