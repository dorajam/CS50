 /**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Author: Dora Jambor, dorajambor@gmail.com
 * October, 2014
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    // Open the memory card
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 1;
    }
    
    int counter = 0;
    FILE* img = NULL;
    
    // Read card onto buffer
    do
    {
        uint8_t buffer[512] = { 0 };
        if (fread(&buffer, sizeof(buffer), 1, card) == 0)
        {
            break;
        }
        
        // Check if it's the start of JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // Close any potentially open JPG
            if (img != NULL)
            {
                fclose(img);
            }
            
            // Make a new JPG
            char pictures[8];
            sprintf(pictures, "%.3i.jpg", counter);
            
            counter++;
    
            // Open the new file
            img = fopen(pictures, "w");
            
            // Write onto your new JPG file until the end of JPG
            fwrite(&buffer, sizeof(buffer), 1, img);  
        }
        else if (img != NULL )
        {
            fwrite(&buffer, sizeof(buffer), 1, img);
        }
    }
    while(!feof(card));
    
    // close all files
    fclose(img);
}
