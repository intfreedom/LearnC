#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main32()
{
      int a[10];
      int i;
      for( i=0; i < 10; i++ )
      {
            scanf("%d", &a[i]);
      }

      printf("\n");
      
      for( i=0; i < 10; i++ )
      {
            printf("%d\n", *(a+i));
      }
}
