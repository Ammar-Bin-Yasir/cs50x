// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
} avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// Sort cities by temperature in descending order using Bubble Sort (more efficient than selection sort for nearly sorted data)
void sort_cities(void)
{
    for (int i = 0; i < NUM_CITIES - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < NUM_CITIES - i - 1; j++)
        {
            if (temps[j].temp < temps[j + 1].temp)
            {
                // Swap temps[j] and temps[j + 1]
                avg_temp temp_swap = temps[j];
                temps[j] = temps[j + 1];
                temps[j + 1] = temp_swap;
                swapped = true;
            }
        }
        // If no swaps occurred, the array is sorted
        if (!swapped)
        {
            break;
        }
    }
}

// // TODO: Sort cities by temperature in descending order
// void sort_cities(void)
// {
//     // Selection Sort
//     int swap_temp = 0;
//     string  swap_city = 0;
//     int T = 0;
//     int max_index = 0;
//     for (int i = 0; i < NUM_CITIES; i++)
//     {
//         T = 0;
//         for (int j = i; j < NUM_CITIES; j++)
//         {
//             //  Decending order
//             if (temps[j].temp > T)
//             {
//                 T = temps[j].temp;
//                 max_index = j;
//             }
//         }
//         // Swap the place of max_index and the first element in the array and so on
//         swap_city = temps[i].city;
//         swap_temp = temps[i].temp;

//         temps[i].city = temps[max_index].city;
//         temps[i].temp = temps[max_index].temp;

//         temps[max_index].city = swap_city;
//         temps[max_index].temp = swap_temp;
//     }
// }
