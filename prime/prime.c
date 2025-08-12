#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

// bool prime(int number)
// {
//     // Check if a number is prime or not
//     if (number == 2)
//         return true;
//     else if (number == 1)
//         return false;
//     else
//     {
//         // Square root the number
//         int root_num = (int) round(sqrt(number));

//         // Check for prime
//         for (int n = 2; n < root_num + 1; n++)
//         {
//             if (number % n == 0)
//                 return false;
//         }
//     }
//     return true;
// }

bool prime(int number)
{
    // Check if a number is prime or not

    if (number == 2)
        return true;
    else if (number == 1)
        return false;
    else
    {
        for (int n = 2; n < number; n++)
        {
            if (number % n == 0)
                return false;
        }
    }
    return true;
}
