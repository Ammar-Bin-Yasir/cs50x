#include <cs50.h>
#include <stdio.h>

int checksum(long number);

int main(void)
{
    // prompt user for an input which is a number
    long number;
    do
    {
        number = get_long("Enter The number: ");
    }
    while (number < 0);

    // Calculate the checksum
    int digit = checksum(number);

    // Check if the number is ligit or not by looking at the unit digit
    if (digit % 10 == 0)
    {
        // Checking the Length of the digits
        int length = 0;
        long temp = number;
        while (temp > 0)
        {
            temp /= 10;
            length++;
        }

        // Extract starting digits
        long start_digits = number;
        while (start_digits >= 100)
        {
            start_digits /= 10;
        }

        // Pint AMEX, VISA, MASTERCARD, INVALID
        if (length == 15 && (start_digits == 34 || start_digits == 37))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && (start_digits >= 51 && start_digits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 13 || length == 16) && (start_digits / 10 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int checksum(long number)
{
    // Calculate the checksum
    int sumld = 0;
    int sumsld = 0;

    while (number > 0)
    {
        // Separates the last digit of the number and sums it in sumld
        int ldigit = number % 10;
        number /= 10;
        sumld += ldigit;

        // Separates the 2nd last digit of the number, multiply by 2 and sums the digits in sumsld
        if (number > 0)
        {
            int sldigit = number % 10;
            number /= 10;
            sldigit *= 2;
            if (sldigit > 9)
            {
                sumsld += sldigit / 10 + sldigit % 10;
            }
            else
            {
                sumsld += sldigit;
            }
        }
    }
    int sum = sumld + sumsld;
    return sum;
}
