#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int letters(string text);
int words(string text);
int sentences(string text);
int CL_index(float L_avg, float S_avg);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int L = letters(text);
    int W = words(text);
    int S = sentences(text);

    // Get the average of letters and sentences
    float L_avg = (float) L / W * 100.0;
    float S_avg = (float) S / W * 100.0;

    // Compute the Coleman-Liau index
    int index = CL_index(L_avg, S_avg);
    // Print the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf(" Grade %i\n", index);
    }
    return 0;
}

int letters(string text)
{
    // I would retrun this value later and It would be the total letters in the text
    int letters = 0;

    // loop to iterate the length of the string and see of somthing is a letter or not
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // checks if the character is alphabet or not
        if (isalpha(text[i]))
            letters++;
    }
    return letters;
}

int words(string text)
{
    // I would return this value later I it would be the total words in the text
    int words = 0;

    // loop to iterate the length of the string
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // check if there is a white space in the string or not
        if (isspace(text[i]))
        {
            words++;
        }
    }
    words++;
    return words;
}

int sentences(string text)
{
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] == '!') || (text[i] == '.') || (text[i] == '?'))
        {
            sentences++;
        }
    }
    return sentences;
}

int CL_index(float L_avg, float S_avg)
{
    float index = 0.0588 * L_avg - 0.296 * S_avg - 15.8;
    return (int) round(index);
}
