#include<cs50.h>
#include<stdio.h>
int main(void)
{
  int n;
  do
  {
      n = get_int("Height: ");
  }
    while(n <1 || n>8);
    int count = 0;
    for(int y=0;y<n; y++)
    {
        for (int space = (n-1) - count; space>0;space--)
        {
            printf(" ");
        }
        for (int x =0 ; x<=count; x++)
        {
            printf("#");
        }
        printf("  ");
        for (int x= 0; x<= count; x++)
        {
            printf("#");
        }
        printf("\n");
        count++;
    }

}