/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 * Dora Jambor
 * October, 2014
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

// define node type
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// size of hashtable
#define SIZE 676

/**
 * Hashing the new word
 */
int hash(const char* word)
{
    // Calculate how the index will change with the first character
    int distance = (tolower(word[0]) - 'a')%26;
    int first_char = 0;
    first_char = first_char + 26*distance;
    int index = 0;
            
    // if the word is longer than a character
    if (word[1] != '\0')
    {
        int asci = 'A';   
        // if next character is low and not apostrophe
        if (islower(word[1]) && word[1] != '\'')
        {
            asci = 'a';
        }
        // if next character is apostrophe
        else if (word[1] == '\'')
        {
            // then word goes to the first bucket that belongs to the first character
            index = first_char;
            return index;
        }
        index = first_char + (word[1] - asci)%26;
        return index;
    }
    else
    {
        // if word is only one character
        int asci = 'a';
        index = (tolower(word[0])- asci) % 26;     
        return index;  
    }
}

// hashtable info
node* hashtable[SIZE] = {NULL};

// declare size of dictionary
int size_of_dict = 0;
 
bool load(const char* dictionary)
{
    // Open dictionary
    FILE* pointer_to_dic = fopen(dictionary, "r");
    
    // check if file is opened now
    if (pointer_to_dic == NULL)
    {
        printf("Can't open dictionary.\n");
        return 1;
    }  
    
    // Declare index and new node for hashtable
    int index;
    
    // Declare word to store strings
    char word[LENGTH + 1]; 
        
    // Read each word from dictionary
    while(fscanf(pointer_to_dic, "%s\n", word) != EOF)
    {   
        // Make a new node for each word 
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        
        // Copy word in new node
        strcpy(new_node->word, word);
        
        // Increment size of dictionary
        size_of_dict++;
        
        // Hash the word
        index = hash(word);
        
        // Link nodes
        if (hashtable[index] == NULL)
        {
            new_node->next = NULL;
            hashtable[index] = new_node;
        }
        
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
    }  
    
    // Close file
    fclose(pointer_to_dic);
    
    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // Hash the word to get index   
    int index = hash(word);
    
    // if hashtable is empty
    if (hashtable[index] == NULL)
    {
        return false;
    }
    
    // get length of word
    int length = strlen(word);
    char word_lower[length + 1];
    
    // set all characters to small letters
    for (int i = 0; i < length; i++)
    {
        word_lower[i] = tolower(word[i]);
    }
    
    // mark the end of the word
    word_lower[length] = '\0';
    
    // Check if word is in the hashtable
    node* cursor = hashtable[index];
    
    while(cursor != NULL)
    {
        if (strcmp(cursor->word, word_lower) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return size_of_dict;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // create temporary node
    node* temp = NULL;
    
    // set cursor to beginning
    for (int i = 0; i < SIZE; i++)
    {
        // if bucket is non-zero, then set cursor to the beginning, and start looping through linked list
        if (hashtable[i] != NULL)
        {
            node* cursor = hashtable[i];
            while (cursor != NULL)
            {
                temp = cursor;
                cursor = cursor->next;
                free(temp);
            }
        }
    }
     
    return true;
}
