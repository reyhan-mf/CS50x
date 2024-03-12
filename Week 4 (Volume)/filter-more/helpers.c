#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < height; row++)
    {
        for(int cols = 0; cols < width; cols++)
        {
          double a = (image[row][cols].rgbtRed + image[row][cols].rgbtBlue + image[row][cols].rgbtGreen) / (3.0);
           image[row][cols].rgbtRed = round(a);
           image[row][cols].rgbtGreen = round(a);
           image[row][cols].rgbtBlue  = round(a);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_temp[height][width];

    for(int row = 0; row < height; row++)
    {
        for(int cols = width - 1; cols >= 0; cols--)
        {
            image_temp[row][width - 1 - cols] = image[row][cols];
        }
    }

    for(int rows = 0; rows < height; rows++)
    {
        for(int cols = 0; cols < width; cols++)
        {
            image[rows][cols] = image_temp[rows][cols];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for(int row = 0; row < height; row++)
    {
        for(int cols = 0; cols < width; cols++)
        {
            copy_image[row][cols] = image[row][cols];
        }
    }

    for(int row = 0; row < height; row++)
    {
        for(int cols = 0; cols < width; cols++)
        {
            int red = 0, blue = 0, green = 0;
            float counter = 0.0;
            for(int i = row - 1; i <= row + 1; i++)
            {
                for(int j = cols - 1; j <= cols + 1; j++)
                {
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {
                        red += copy_image[i][j].rgbtRed;
                        blue += copy_image[i][j].rgbtBlue;
                        green += copy_image[i][j].rgbtGreen;
                        counter++;
                    }
                }
            }
                image[row][cols].rgbtRed = round(red / counter);
                image[row][cols].rgbtBlue = round(blue / counter);
                image[row][cols].rgbtGreen = round(green / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1}};

    RGBTRIPLE copy_image[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int cols = 0; cols < width; cols++)
        {
            copy_image[row][cols] = image[row][cols];
        }
    }

    int red_x = 0, red_y = 0, blue_x = 0, blue_y = 0, green_x = 0, green_y = 0;
    int total_red, total_blue, total_green;

    for (int row = 0; row < height; row++)
    {
        for (int cols = 0; cols < width; cols++)
        {
            total_red = total_blue = total_green = 0;

            for (int i = row - 1; i <= row + 1; i++)
            {
                for (int j = cols - 1; j <= cols + 1; j++)
                {
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {
                        red_x += copy_image[i][j].rgbtRed * Gx[i - row + 1][j - cols + 1];
                        blue_x += copy_image[i][j].rgbtBlue * Gx[i - row + 1][j - cols + 1];
                        green_x += copy_image[i][j].rgbtGreen * Gx[i - row + 1][j - cols + 1];

                        red_y += copy_image[i][j].rgbtRed * Gy[i - row + 1][j - cols + 1];
                        blue_y += copy_image[i][j].rgbtBlue * Gy[i - row + 1][j - cols + 1];
                        green_y += copy_image[i][j].rgbtGreen * Gy[i - row + 1][j - cols + 1];
                    }
                }
            }

            total_red = round(((sqrt(red_x * red_x + red_y * red_y))));
            total_blue = round(sqrt(blue_x * blue_x + blue_y * blue_y));
            total_green = round(sqrt(green_x * green_x + green_y * green_y));
            red_x = red_y = blue_x = blue_y = green_x = green_y = 0;
            if (total_red > 255)
            {
                total_red = 255;
            }
            if (total_blue > 255)
            {
                total_blue = 255;
            }
            if (total_green > 255)
            {
                total_green = 255;
            }

            image[row][cols].rgbtRed = total_red;
            image[row][cols].rgbtBlue = total_blue;
            image[row][cols].rgbtGreen = total_green;
        }
    }
    return;
}
