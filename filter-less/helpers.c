#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray_value;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gray_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gray_value;
            image[i][j].rgbtGreen = gray_value;
            image[i][j].rgbtRed = gray_value;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int max = 255;
    RGBTRIPLE original;
    RGBTRIPLE sepia;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original.rgbtRed = image[i][j].rgbtRed;
            original.rgbtGreen = image[i][j].rgbtGreen;
            original.rgbtBlue = image[i][j].rgbtBlue;
            int rgbtRed = round((.393 * original.rgbtRed) + (.769 * original.rgbtGreen) + (.189 * original.rgbtBlue));
            if (rgbtRed <= 255)
            {
                sepia.rgbtRed = rgbtRed;
            }
            else
            {
                sepia.rgbtRed = 255;
            }
            int rgbtGreen = round((.349 * original.rgbtRed) + (.686 * original.rgbtGreen) + (.168 * original.rgbtBlue));
            if (rgbtGreen <= 255)
            {
                sepia.rgbtGreen = rgbtGreen;
            }
            else
            {
                sepia.rgbtGreen = 255;
            }
            int rgbtBlue = round((.272 * original.rgbtRed) + (.534 * original.rgbtGreen) + (.131 * original.rgbtBlue));
            if (rgbtBlue <= 255)
            {
                sepia.rgbtBlue = rgbtBlue;
            }
            else
            {
                sepia.rgbtBlue = 255;
            }
            image[i][j].rgbtRed = sepia.rgbtRed;
            image[i][j].rgbtGreen = sepia.rgbtGreen;
            image[i][j].rgbtBlue = sepia.rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the pixel at the current index with the pixel at the opposite index horizontally
            temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int averageRed;
    int averageBlue;
    int averageGreen;
    // Copy 2D array for reference
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Loop through 2D array to find focus
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // If current focus is top left corner
            if (i == 0 && j == 0)
            {
                averageRed =
                    round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4.0);
                averageGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4.0);
                averageBlue =
                    round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4.0);
            }
            // If current focus is top right corner
            else if (i == 0 && j == width - 1)
            {
                averageRed =
                    round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed
                           + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 4.0);
                averageGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen
                           + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 4.0);
                averageBlue =
                    round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue
                           + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 4.0);
            }
            // If current focus is bottom left corner
            else if (i == height - 1 && j == 0)
            {
                averageRed =
                    round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                           + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                averageGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                           + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) / 4.0);
                averageBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                           + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
            }
            // If current focus is bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                averageRed =
                    round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed
                           + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) / 4.0);
                averageGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen
                           + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) / 4.0);
                averageBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue
                           + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) / 4.0);
            }
            // If current focus is along top edge
            else if (i == 0)
            {
                averageRed =
                    round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed
                           + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                averageGreen =
                    round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen
                           + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                averageBlue =
                    round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue
                           + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            // If current focus is along bottom edge
            else if (i == height - 1)
            {
                averageRed =
                    round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                           + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) / 6.0);
                averageGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                           + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) / 6.0);
                averageBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                           + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) / 6.0);
            }
            // If current focus is along left edge
            else if (j == 0)
            {
                averageRed =
                    round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                           + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed
                           + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                averageGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                           + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen
                           + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                averageBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                           + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue
                           + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
            }
            // If current focus is along right edge
            else if (j == width - 1)
            {
                averageRed =
                    round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed
                           + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed
                           + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 6.0);
                averageGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen
                           + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen
                           + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 6.0);
                averageBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue
                           + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue
                           + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 6.0);
            }
            // If current focus is not along an edge
            else
            {
                averageRed =
                    round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                           + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed
                           + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);
                averageGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                           + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen
                           + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);
                averageBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                           + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue
                           + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
            }
            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtBlue = averageBlue;
        }
    }
    return;
}
