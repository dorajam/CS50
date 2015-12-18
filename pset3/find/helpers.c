/**
 helpers.c
 Computer Science 50
 Problem Set 3

 Author: Dora Jambor, dorajambor@gmail.com
 September, 2014 

Helper functions for Problem Set 3. with binary search and insertion sort
 */
       
#include <cs50.h>
#include <stdbool.h>
#include "helpers.h"

/**
 * Using binary search, returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int start = 0;
    int end = n - 1;
    
    // Check if the length of the list is greater than 0
    while(end >= start)
    {
        // Check if value is at the middle of the 
        int middle = (start + end) / 2;
        if(values[middle] == value)
        {
            // Return true if value is found
            return true;
        }
        
        // If value is to the right of the middle
        else if(values[middle] < value)
        {
            start = middle + 1;
        }
        
        // If value is to the left of the middle
        else
        {
            end = middle - 1;
        }
    }
    return false;
}

/**
 * Using insertion sort, sort array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 0; i < n; i++)
    {
        // Declare element that's currently moving into sorted portion
        int element = values[i];
        
        int j = i;
        
        // Iterate through sorted portion
        while(j > 0 && values[j - 1] > element)
        {
            // Make space for new sorted element
            values[j] = values[j - 1];
            j = j - 1;
        }
        
        // Insert new element
        values[j] = element;
    }
    return;
}
