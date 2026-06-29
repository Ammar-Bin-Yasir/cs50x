#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get the amount of numbers that you want to print
    int n = get_int("Type the total amount of numbers: ");

    //make an array of the number user input
    int numbers[n];

    //print the required number sequence
    for (int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            numbers[i] = 1;
        printf("%i, ", numbers[i]);

        }
        else 
        {
            numbers[i] = numbers[i - 1] * 2;
        printf("%i, ", numbers[i]);
        }
    }
    printf("\n");
}
