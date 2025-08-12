#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickles(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give customer
    int quarters = calculate_quarters(cents);

    // Subtract the value of those quarters from cents
    cents = cents - (quarters * 25);

    // Calculate how many dimes you should give customer
    int dimes = calculate_dimes(cents);

    // Subtract the value of those dimes from remaining cents
    cents = cents - (dimes * 10);

    // Calculate how many nickels you should give customer
    int nickles = calculate_nickles(cents);

    // Subtract the value of those nickels from remaining cents
    cents = cents - (nickles * 5);

    // Calculate how many pennies you should give customer
    int pennies = calculate_pennies(cents);

    // Subtract the value of those pennies from remaining cents
    cents = cents - (pennies * 1);

    int change = quarters + dimes + nickles + pennies;

    printf("%i\n", change);
}

int calculate_quarters(int cents)
{
    // Calculate how many quarters you should give customer
    int quarters = 0;

    for (int n = 1; cents >= 25; n++)
    {
        quarters = n;
        cents = cents - 25;
    }

    return quarters;
}

int calculate_dimes(int cents)
{
    // Calculate how many dimes you should give customer
    int dimes = 0;

    for (int n = 1; cents >= 10; n++)
    {
        dimes = n;
        cents = cents - 10;
    }

    return dimes;
}

int calculate_nickles(int cents)
{
    // Calculate how many nickels you should give customer
    int nickles = 0;

    for (int n = 1; cents >= 5; n++)
    {
        nickles = n;
        cents = cents - 5;
    }

    return nickles;
}

int calculate_pennies(int cents)
{
    // Calculate how many pennies you should give customer
    int pennies = 0;

    for (int n = 1; cents >= 1; n++)
    {
        pennies = n;
        cents = cents - 5;
    }

    return pennies;
}
