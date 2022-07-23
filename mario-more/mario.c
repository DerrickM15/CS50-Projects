#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask for the height and validate
    int height;
    int blocks;
    do
    {
        // collect height input from user, 1 - 8
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    blocks = height;
    // for each row
    for (int i = 1; i <= height; i++)
    {
        // for each column
        for (int j = 1; j <= height; j++)
        {
            if (j < blocks)
            {
                printf(" ");
            }
            else if (j >= blocks)
            {
                printf("#");
            }
            if (j == height)
            {
                printf("  ");
            }
        }
        for (int k = height; k >= 1; k--)
        {
            if (k >= blocks)
            {
                printf("#");
            }
        }
        // move to next row and decrement blocks
        printf("\n");
        blocks--;
    }
}