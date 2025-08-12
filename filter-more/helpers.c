#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each row for the image
    for (int i = 0; i < height; i++)
    {
        // Iterate through the coulmns of the row(Each pixel)
        for (int j = 0; j < width; j++)
        {
            // Calculate the average value for the pixel
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Change the RGB value of each pixel to the avg
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Iterate over each coulmn (pixel)
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the pixels of the row such that
            // Far right pixel becomes the far left and vice virsa
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temperary array
    RGBTRIPLE temp[height][width];
    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel
        for (int j = 0; j < width; j++)
        {
            // Initialize accumulators;
            int R = 0;
            int G = 0;
            int B = 0;
            int npixels = 0;

            // For each pixel calculate the averages of the RGB values of pixels within 1 mile
            // radius Iterate over the 3 rows around the main pixel
            for (int di = -1; di <= 1; di++)
            {
                // Iterate over the 3 pixels of each the rows
                for (int dj = -1; dj <= 1; dj++)
                {
                    // Incriment the
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Counter of valid pixels
                        npixels += 1;
                        // sum the RBG values all the neighbouring pixels
                        B += image[ni][nj].rgbtBlue;
                        G += image[ni][nj].rgbtGreen;
                        R += image[ni][nj].rgbtRed;
                    }
                }
            }
            // assign the value of the RGB to the main pixel
            temp[i][j].rgbtBlue = round((float) B / npixels);
            temp[i][j].rgbtGreen = round((float) G / npixels);
            temp[i][j].rgbtRed = round((float) R / npixels);
        }
    }

    // Second set of loops
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // Iterate over each row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel
        for (int j = 0; j < width; j++)
        {
            // Initialize variables to compute Gx and Gy
            typedef struct
            {
                int r;
                int g;
                int b;
            } RGBSUM;

            RGBSUM sGx = {0, 0, 0};
            RGBSUM sGy = {0, 0, 0};
            RGBSUM magnitude_G = {0, 0, 0};

            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
            // Iterate over the 3 rows around the main pixel
            for (int di = -1; di <= 1; di++)
            {
                // Iterate over the 3 pixels of each the rows
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Condition to see if the neighboring pixels is within the image
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Sum all the Gx values
                        sGx.r += image[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                        sGx.g += image[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                        sGx.b += image[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];

                        // Sum all the Gy values
                        sGy.r += image[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                        sGy.g += image[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                        sGy.b += image[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }
            // Compute the final Magnitude for all the RGB channels
            magnitude_G.r = round(sqrt((sGx.r * sGx.r) + (sGy.r * sGy.r)));
            if (magnitude_G.r > 255)
            {
                magnitude_G.r = 255;
            }
            magnitude_G.g = round(sqrt((sGx.g * sGx.g) + (sGy.g * sGy.g)));
            if (magnitude_G.g > 255)
            {
                magnitude_G.g = 255;
            }
            magnitude_G.b = round(sqrt((sGx.b * sGx.b) + (sGy.b * sGy.b)));
            if (magnitude_G.b > 255)
            {
                magnitude_G.b = 255;
            }
            // Update the pixel values
            temp[i][j].rgbtRed = magnitude_G.r;
            temp[i][j].rgbtGreen = magnitude_G.g;
            temp[i][j].rgbtBlue = magnitude_G.b;
        }
    }
    // Loop to assign value from temp array to the orignal
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// TODO: Compute the Gx and Gy for each channel of red, green, blue .

// For pixels at the boarder, treat any pixel past the boarder as having all 0 values
// Treat the image as if there was a 1 pixel solid black border around the edge of the image

// Compute the new channel value as the sqrt Gx^2 + Gy^2

// And since channel values can only take on integer values from 0 to 255,
// be sure the resulting value is rounded to the nearest integer and capped at 255!
