#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for Height
    int height;
    do
    {
        height = get_int("Enter the height: ");
    }
    while (height < 1 || height > 8);


    // Iterate over the pryamid rows
    for (int row = 1; row <= height; row++)
    {
        // Print the Space
        // e.g if height = 5, row = 1, spaces printed will be 4, the fifth would be the hash
        for (int space = 0; space < height - row; space++)
        {
            printf(" ");
        }

        // Print the Hashes
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        }

        printf("\n");
    }
}
