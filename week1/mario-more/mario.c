#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int Height;
    do
    {
        Height = get_int("Enter The Height: ");
    }
    while (Height < 1 || Height > 8);

    for (int row = 1; row <= Height; row++)
    {
        // Print leading spaces
        for (int space = 0; space < Height - row; space++)
        {
            printf(" ");
        }

        // Print left pyramid
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        }

        // Print gap
        printf("  ");

        // Print right pyramid
        for (int hash = 0; hash < row; hash++)
        {
            printf("#");
        }

        // Move to the next line
        printf("\n");
    }
}
