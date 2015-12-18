/*
greedy.c

Author: Dora Jambor, dorajambor@gmail.com
September, 2014

This is the solution to the greedy algorithm problem from pset1 of CS50
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float input;
    int coin[] = {25, 10, 5, 1};
    int sum = 0;
    
    // ask for change in dollars and convert into cents
    do
    {
        printf("How much change do I owe you in dollars? ");
        input = GetFloat();
    }
    while (input < 0);
    
    int cents = round(input * 100);
    
    // get the minimum number of coins
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        sum = sum + cents / coin[i];
        cents = cents%coin[i];
    }
    
    printf("%d\n", sum);
    return 0;
}
