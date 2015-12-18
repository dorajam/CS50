/*
initials.c

Author: Dora Jambor, dorajambor@gmail.com
September, 2014

Returns the initials of the user's name
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    printf("Tell me your name: ");
    string s = GetString();
    if (!s) 
    {
        printf("Try again!");
    return 0;
    }
    printf("%c", toupper(s[0]));
    for(int i = 0; i < strlen(s); i++)
    {
        if(s[i] == ' ')
            {
            printf("%c", toupper(s[i+1]));
            }
    }
}
