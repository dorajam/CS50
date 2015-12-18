/*
vigenere.c

Author: Dora Jambor, dorajambor@gmail.com
September, 2014

Encrypts a plaintext by using a sequence of keys;
Demonstrates the use of vigenere cipher
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    // Check the validity of the key
    if(argc != 2)
    {
        printf("Please follow: ./caesar key\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        
        for(int i = 0, n = strlen(key); i < n; i++)
        {
            if(!isalpha(key[i]))
            {
                printf("Please follow: ./caesar key\n");
                return 1;
            }
        }
        
        // Get the text
        string text = GetString();
        
        // Convert characters of key and plaintext into alphabetical numbers
        int p = 0;
        for(int j = 0, n = strlen(text); j < n; j++)
        {
            if(isalpha(text[j]))
            {
                // Encrypt both small and capital letters with the key
                int convert[] = {97, 65};
                int k = 0;
                p = j;
                if(!isalpha(text[j-1]) && j > 0)
                    p++;
                int number = tolower(text[j]);
                int shiftkey = tolower(key[p%strlen(key)]);

                if(isupper(text[j]))
                {
                    k = 1;
                    number = toupper(text[j]);
                    shiftkey = toupper(key[p%strlen(key)]);
                }
                number = number - convert[k];
                shiftkey = shiftkey - convert[k];
                int result = (number + shiftkey)%26;
                result = result + convert[k];
                char cipher = result;
                printf("%c", cipher);
            }
            else
            {
                printf("%c", text[j]);
            }
        }
        printf("\n");   
    }
}
