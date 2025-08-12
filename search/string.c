#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // An array of strings
    string strings[] = {"battleships", "top hat", "boot", "cannon", "iron", "thimble"};

    // Search for string
    string s = get_string("String: ");
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            printf("Found \n");
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
}
