#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int letter_counter(string s, int letter_count);
int word_count(string s , int word_count);
int count_sentences(string s , int sen_count);
int main(void)
{
    // get input from user.
    char *s = get_string("Text: ");
    // cout letters from text.
    int letter_count = 0;
    int letters = letter_counter(s, letter_count);
    // count words from text.
    int word_counter =0;
    int words = word_count(s, word_counter);
    //count sentences from text.
    int sen =0;
    int sentences = count_sentences(s, sen);
    float L = 0.0588 * (float)letters/ words*100;
    float S = 0.296 * (float)sentences/ words*100;
     float index = L - S - 15.8;
    int grade = round(index);

    if(grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if(grade >=16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n",grade );
    }


}
// function for counting letters.
int letter_counter(string s, int letter_count)
{
    letter_count =0;
    for (int i =0, n = strlen(s); i <= n; i++)
    {
       if ((64 <s[i] && s[i] < 91) || (96 < s[i] && s[i] < 123) )
        {
            letter_count++;
        }
     }
        return letter_count;
}
// function for counting words.
int word_count(string s , int word_count)
{
    word_count = 1;
    for (int i = 0, n = strlen(s); i<n; i++)
    {
        if (s[i] == 32)
        {
            word_count++;
        }
    }
    return word_count;

}
// function for counting sentences.
int count_sentences(string s, int sen_count)
{
     sen_count = 0;
     for(int i = 0, n = strlen(s); i<n; i++)
     {
        if( s[i] == 33 || s[i] == 46 || s[i] == 63)
        {
            sen_count++;
        }
     }
     return sen_count;
}

