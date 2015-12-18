/*
mario.c

Author: Dora Jambor, dorajambor@gmail.com
September, 2014

This is the solution to the mario problem from pset1 of CS50
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Please enter the height of half-pyramid: ");
        height = GetInt();
    }
    while (height <= 0 || height >= 23);
  
    for (int i = height; i > 0; i--)
        {
                for (int j = 0; j < i; j++)
                {
                    printf(" ");
                }
                for (int j = i; j <= height; j++)
                {
                    printf("#");
                }
                
        printf("\n");
        }
}
