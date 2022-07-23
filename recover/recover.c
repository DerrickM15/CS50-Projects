#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



int main(int argc, char *argv[])
{
    //Assign global variables and global data types
    typedef uint8_t BYTE;
    int BLOCK_SIZE = 512;
    int count = 0;
    BYTE buffer[BLOCK_SIZE - 1];
    char *fileName = malloc(4);
    FILE *output = NULL;

    // Error if missing imput file argument
    if (argc < 2)
    {
        printf("missing argument\n");
        return 1;
    }
    //Error if too many arguments are provided
    if (argc > 2)
    {
        printf("too many arguments\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];

    // Open input file
    FILE *input = fopen(infile, "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }
    // Loop through
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // When found beginning bytes signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Write incrementing file name
            sprintf(fileName, "%03i.jpg", count);
            // Open output file
            output = fopen(fileName, "w");
            count++;

        }
        if (count != 0)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, output);
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}