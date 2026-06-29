// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

string replace(string word);

int main(int argc, string argv[])
{
    // Check for Command line arguments
    if (argc != 2)
    {
        printf("Usage: ./filename word\n");
        return 1;
    }
    else
    {
        string word = replace(argv[1]);
        // Convert the vowels in the word with numbers
        printf("%s\n", word);
        free(word);
    }
}

string replace(string word)
{
    string new_word = malloc(strlen(word) + 1);
    strcpy(new_word, word);
    // Iterate over the word given
    for (int i = 0, n = strlen(new_word); i < n; i++)
    {
        switch (word[i])
        {
            case 'a':
            case 'A':
                new_word[i] = '6';
                break;
            case 'e':
            case 'E':
                new_word[i] = '3';
                break;
            case 'i':
            case 'I':
                new_word[i] = '1';
                break;
            case 'o':
            case 'O':
                new_word[i] = '0';
                break;
        }
    }
    return new_word;
}
