// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    // Convert the percentages to decimal values
    tax /= 100;
    float ntip = (float) tip / 100;

    // add the bill and the tax
    float ntax = bill * tax;
    float nbill = bill + ntax;

    // calculate and add the tip
    ntip = nbill * ntip;
    nbill += ntip;

    // Half the bill
    nbill /= 2;

    return nbill;
}
