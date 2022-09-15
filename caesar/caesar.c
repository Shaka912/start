#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void rotate(string s, int key);
int main(int argc, string argv[])
{
    // for checking cmd-line argument.
    if (argc == 2)
    {
        int key = atoi(argv[1]);
        bool key_value = false;
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]))
            {
               key_value = true;
            }
            else
            {
               printf("Usage: ./caesar key\n");
               return 1;
           }
       }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string s = get_string("Plain-Text:  ");
    rotate(s, key);
}
void rotate (string s,int key)
{
    printf("ciphertext: ");
    int c = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
      {
        if(isalpha(s[i]))
        {
           if(isupper(s[i]))
           {
                c =((s[i] - 65 + key) % 26) + 65;
                printf("%c", c);
            }
                else if (islower(s[i]))
            {
                c =((s[i] -97 + key) % 26) + 97;
                printf("%c", c);
            }
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}

