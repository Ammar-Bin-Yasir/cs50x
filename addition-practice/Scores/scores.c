#include <cs50.h>
#include <stdio.h>

int N;

float average(int totalnumbers, int array[]);

int main (void)
{
    N = get_int("Total Numbers: ");
    //Get Scores
    int scores[N];
   for (int i = 0; i < N; i++)
   {
    scores[i] = get_int("Score: ");
   }

   //Print Average
   printf("Average %f\n", average(N, scores));
}

float average(int totalnumbers, int array[])
{
    //calculate Average
    int sum = 0;
    for (int i = 0; i < totalnumbers; i++)
    {
        sum += array[i];
    }
    return sum / (float) totalnumbers;
}

