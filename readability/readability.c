#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string letters);
int count_words(string words);
int count_sentences(string sentences);

int main(void)
{
    string text = get_string("Text: ");
    int lettercount = count_letters(text);
    int wordcount = count_words(text);
    int sentencecount = count_sentences(text);

    /*
    printf("%i letters\n", lettercount);
    printf("%i words\n", wordcount);
    printf("%i sentences\n", sentencecount);
    */

    // Initialize int variables for per 100 words, average sentences per 100 words, and average letters per 100 words
    float S = (((float) sentencecount / wordcount) * 100.0);
    float L = (((float) lettercount / wordcount) * 100.0);
    // Grade calculation
    int grade = round(0.0588 * L - 0.296 * S - 15.8);
    // Print grade based on provided grade-year range
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

int count_letters(string letters)
{
    int count = 0, l = 0;
    // Loop through passed string
    for (int i = 0; i <= strlen(letters); i++)
    {
        l = letters[i];
        //if the lowercased char at index i is between a-z
        if (tolower(l) >= 97 && tolower(l) <= 122)
        {
            // increase count by 1
            count++;
        }
    }
    return count;
}

int count_words(string words)
{
    int wcount = 1, w = 0;
    // Loop through passed string
    for (int i = 0; i <= strlen(words); i++)
    {
        w = words[i];
        // If char at index i is space
        if (w == 32)
        {
            // Increase word count by 1
            wcount++;
        }
    }
    return wcount;
}

int count_sentences(string sentences)
{
    int scount = 0, s = 0;
    for (int i = 0; i <= strlen(sentences); i++)
    {
        s = sentences[i];
        if (s == 33 || s == 46 || s == 63)
        {
            scount++;
        }
    }
    return scount;
}