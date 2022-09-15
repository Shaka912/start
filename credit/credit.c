#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int sum1 =0;
    int sum2 =0;
    int num = 0;
    int remainder =0;
    long cardNumber;
    do
    cardNumber = get_long("Please enter your card number: ");
    while (cardNumber<1);
    long temp = cardNumber;
    while (temp >0)
    {
        num = ((temp/10)%10)*2; // multiplying every other digit by 2 from last to start
         while (num>0)
         {
             remainder = num%10;
             sum1 += remainder; // adding the product
             num /=10;
         }
         temp /=100;
    }
    remainder = 0;
    temp = cardNumber;
      while(temp>0)
      {
          remainder = temp%10;
          sum2 += remainder; // sum of the digits that was not multiplied
          temp /= 100;
      }
       if ((sum1+sum2)%10 == 0)
       {
           printf("Valid card\n VISA\n");
       }
       else
       {
           printf("The card is Invalid\n");
       }
       return 0;
}