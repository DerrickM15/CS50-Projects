#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(string ptext, string key);
string keycheck(string uncheckedkey);

int main(int argc, string argv[])
{
    // Declare variables
    string plaintext;

    // If there are too few arguments
    if (argc < 2)
    {
        // Print error and exit
        printf("usage: ./substitution key\n");
        return 1;
    }
    // If there are more than 2 arguments
    else if (argc > 2)
    {
        // Print error and exit
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // If key does not contain any characters
    else if (strlen(argv[1]) > 0 && strlen(argv[1]) < 26)
    {
        // Print error and exit
        printf("Key must contain 26 characters. \n");
        return 1;
    }
    string key = keycheck(argv[1]);
    // If key contains invalid characters
    if (strcmp(key, "invalid") == 0)
    {

        // Print error and exit
        printf("Key must only contain alphabet\n");
        return 1;
    }
    // If key contains duplicates
    else if (strcmp(key, "duplicate") == 0)
    {
        // Print error and exit
        printf("Key cannot contain duplicates\n");
        return 1;
    }
    else
    {
        // Assign argument to variable and run encryption function
        plaintext = get_string("plaintext: ");
        encrypt(plaintext, key);
    }
}

string keycheck(string uncheckedkey)
{
    for (int i = 0; i < strlen(uncheckedkey); i++)
    {
        for (int j = i + 1; j < strlen(uncheckedkey); j++)
        {
            // If key contains duplicates return trigger
            if (toupper(uncheckedkey[i]) == toupper(uncheckedkey[j]))
            {
                return "duplicate";
            }
        }
    }
    for (int i = 0; i < strlen(uncheckedkey); i++)
    {
        if ((int) toupper(uncheckedkey[i]) < 65 || (int) toupper(uncheckedkey[i]) > 91)
        {
            // If key contains duplicates return trigger
            return "invalid";
        }
    }
    return uncheckedkey;
}


void encrypt(string ptext, string key)
{
    printf("ciphertext: ");
    char encryptedchar;
    for (int i = 0; i < strlen(ptext); i ++)
    {
        // If the char at the current index of plaintext is lowercase
        if (islower(ptext[i]))
        {
            // Assign and print the char at the current index of plaintext replaced by the ascii value minus 97 index of key
            encryptedchar = tolower(key[tolower((ptext[i]) - 97)]);
            printf("%c", encryptedchar);
        }
        //  If the char a the current index of plaintext is uppercase
        else if (isupper(ptext[i]))
        {
            // Assign and print the char at the current index of plaintext replaced by the ascii value minus 65 index of key
            encryptedchar = toupper(key[toupper((ptext[i]) - 65)]);
            printf("%c", encryptedchar);
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
}

