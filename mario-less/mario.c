#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while(n<1 || n>8);
    int counter = 0;
    for(int row=0;row<n;row++)
    {
        for (int space = (n-1)-counter ; space >0; space--)
        {
            printf(" ");
        }
        for(int y =0; y<=counter; y++)
        {
            printf("#");
        }
        printf("\n");
        counter++;
    }
}