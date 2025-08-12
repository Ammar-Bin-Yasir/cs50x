// write a program that iterates over a copy of my memory card, looking for JPEGs’ signatures.
// Each time you find a signature, you can open a new file for writing
// and start filling that file with bytes from my memory card
// closing that file only once you encounter another signature.
// rather than read my memory card’s bytes one at a time,
// you can read 512 of them at a time into a buffer for efficiency’s sake
// Recall the possibility of slack space
// It’s okay if those trailing 0s end up in the JPEGs you recover; they should still be viewable.
// ultimately find that the image contains 50 JPEGs.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK = 512;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("The file was not opened.");
        return 1;
    }
    // Create a buffer for a block of data
    uint8_t buffer[BLOCK];
    int count = 0;
    char filename[8];
    FILE *img = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK, card) == BLOCK)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            // Close the previous image if any
            if (img != NULL)
            {
                fclose(img);
            }
            // Create a new filename and open a new file
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            count++;
        }
    // Write the buffer to the current image file if open
    if (img != NULL)
    {
        fwrite(buffer, 1, BLOCK, img);
    }
}

// Close any remaining open files
if (img != NULL)
{
    fclose(img);
}

// Close memory card
fclose(card);
}
