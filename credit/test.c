#include <stdio.h>
#include <cs50.h>
int main(void)
{

    long n;
    int sum = 0;
    do
     n= get_long("Enter card number: ");
    while(n <1);
    long temp = n;
    //1st case
    while (temp>0)
    {
        int lastdigit = temp%10;
        sum = sum + lastdigit;
        temp = temp /100;

    }
    temp = n/10;
    //2nd case
    while (temp>0)
    {
        int lastdigit = temp%10;
        int timestwo = lastdigit *2;
        timestwo = (timestwo %10)+ (timestwo/10);
        sum = sum + timestwo;
        temp= temp/100;
    }
    if (sum %10 == 0 )
    {
        printf("The Card is Valid \n");
    }
    else
    {
        printf("The card is InValid\n");
    }
}