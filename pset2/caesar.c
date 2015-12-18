/*
caesar.c

Author: Dora Jambor, dorajambor@gmail.com
September, 2014

This is the solution to the caesar algorithm problem from pset1 of CS50
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // Get a valid key and convert it into an integer
    if(argc != 2)
    {
        printf("Please follow: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]);
        
        // Get the text
        printf("Please type some plaintext: \n");
        string text = GetString();
    
        // Calculate the ASCII value of each character, and add key
        for(int i = 0, n = strlen(text); i < n; i++)
        {
            if(isalpha(text[i]))
            {
                int number = tolower(text[i]);
                number = number - 97;
                int sum = 0;
                sum = (sum + number + key)%26;
                number = sum + 97;
                char result = number;
                printf("%c", result);
            }
            else
            {
                printf("%c", text[i]);
            }
        }
    }
}
