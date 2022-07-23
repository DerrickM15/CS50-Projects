// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 27946;
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashed = 0, num_in_alphabet = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == '\'')
        {
            num_in_alphabet = 27;
        }
        num_in_alphabet = (toupper(word[i]) - 'A');
        // Sum of the current alphabetical number and base 27 of the current index
        hashed += (num_in_alphabet + i * 27);
    }
    return hashed;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH];
    int num;
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Loop through file's words
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for a node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Copy word to node
        strcpy(n->word, word);
        // Hash word to obtain a hash value
        num = hash(n->word);
        // Assign n->next to the node following it within the hash table
        n->next = table[num];
        // Re-assign table[num] to point at n
        table[num] = n;
        // Count of words within the dictionary
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Returns count variable
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp;
    node *cursor;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
