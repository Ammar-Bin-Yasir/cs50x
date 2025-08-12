#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //Promt user to get their name
    string s = get_string("Before: ");
    printf("After: ");
    //Use a loop to iterate the length of string and make any lowercase character uppercase
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", toupper(s[i]));
    }
    printf("\n");
}
