#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("tie!\n");
    }
}
// Determine the score of a word
int compute_score(string word)
{
    int score = 0;
    // Iterate through the word string until you've reached the end of the string
    for (int i = 0; i <= strlen(word); i++)
    {
        // Determine the ASCII value of the lowercase char at word index i
        int c = tolower(word[i]);
        // Verify char is a lowercase letter
        if (c >= 97 && c <= 122)
        {
            // Increase score by value in POINTS at the index of the ASCII value of char minus 97(lowercase a)
            score += POINTS[c - 97];
        }
    }
    return score;
}
