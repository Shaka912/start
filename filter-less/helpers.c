#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    int aar;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) /3.0;
            aar = round(average);

            image[i][j].rgbtBlue =aar;
            image[i][j].rgbtGreen =aar;
            image[i][j].rgbtRed =aar;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sr;
    int sg;
    int sb;
    float sepiaBlue;
    float sepiaGreen;
    float sepiaRed;
    for(int i =0; i<height; i++)
    {
        for(int j =0; j<width; j++)
        {
            sepiaRed = .393*image[i][j].rgbtRed + .769*image[i][j].rgbtGreen + .189*image[i][j].rgbtBlue;
            sepiaGreen = .349*image[i][j].rgbtRed + .686*image[i][j].rgbtGreen + .168*image[i][j].rgbtBlue;
            sepiaBlue = .272*image[i][j].rgbtRed + .534*image[i][j].rgbtGreen + .131*image[i][j].rgbtBlue;
            sr = round(sepiaRed);
            sg = round(sepiaGreen);
            sb = round(sepiaBlue);
            if(sr >255)
            {
                sr = 255;
                image[i][j].rgbtRed = sr;
            }
            else
            {
                image[i][j].rgbtRed = sr;
            }
            if(sg >255)
            {
                sg = 255;
                image[i][j].rgbtGreen = sg;
            }
            else
            {
                image[i][j].rgbtGreen = sg;
            }
            if(sb >255)
            {
                sb = 255;
                image[i][j].rgbtBlue = sb;
            }
            else
            {
                image[i][j].rgbtBlue = sb;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
     RGBTRIPLE temp;
    int middle = width/2;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<middle; j++)
        {
            temp = image[i][j];
            image[i][j]= image[i][width-j-1];
            image[i][width-j-1]= temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int avgR =0;
    int avgG = 0;
    int avgB = 0;
    int rR = 0;
    int rG = 0;
    int rB = 0;
    float count = 0.0;

// creating a copy of the image
    for(int i =0; i<height; i++)
    {
        for(int j= 0; j<width; j++)
        {
            // coping img to temp var
            temp[i][j] = image[i][j];
        }
    }
    for(int i =0; i< height; i++)
    {
        for(int j = 0; j< width; j++)
        {
             // for creating a 3x3 grid arund the pixel
            for(int k = -1; k<2; k++)
            {
                for(int z = -1; z<2; z++)
                {
                    int currentx = i +k;
                    int currenty= j+z;
                    // checking for edge case
                    if(currentx < 0 || currentx > (height-1) || currenty < 0 || currenty > (width-1))
                    {
                             continue;
                    }
                    else
                    {
                        avgR +=  image[currentx][currenty].rgbtRed ;
                        avgG  += image[currentx][currenty].rgbtGreen;
                        avgB += image[currentx][currenty].rgbtBlue;
                        count++;
                    }
                  }
                    }
                        // calcuating avgerage of pixles
                    float  fR =0.0;
                    float fG = 0.0;
                    float fB = 0.0;
                    fR = avgR / count;
                    fG = avgG / count;
                    fB  = avgB / count;
                    rR = round(fR);
                    rG = round(fG);
                    rB = round(fB);
                    temp[i][j].rgbtRed  =rR;
                    temp[i][j].rgbtGreen = rG;
                    temp[i][j].rgbtBlue = rB;
                    count = 0.00;
                    avgR = 0;
                    avgG = 0;
                    avgB = 0;
                    fR = fG = fB = 0.0;
                    rR =rG = rB = 0;
        }
    }
// coping newly edidited pixls in image
    for(int i = 0; i< height; i++)
    {
        for(int j= 0; j<width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
