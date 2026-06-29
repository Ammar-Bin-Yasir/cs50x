#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string encipher(string input, string argv);

int main(int argc, string argv[])
{
    // Get the Key which would be used to encrypt the message from string argv[]
    // Validate the Key
    // Check the key length(26)
    // Check for non-alphabetic characters
    // Check for repeated characters (case-insensitive)

    // 2 command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    // argv should have 26 elements
    int l = strlen(argv[1]);
    if (l != 26)
    {
        printf("Key must contain 26 letters.\n");
        return 1;
    }

    // loop to see if the provided key is alphabet or not
    for (int i = 0; i < l; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key should be all alphabets\n");
            return 1;
        }
    }

    // Loop to see if a letter is repeating or not
    // Make a check array
    int seen[26] = {0};

    for (int i = 0; i < l; i++)
    {
        int index = tolower(argv[1][i]) - 'a';
        if (seen[index] == 1)
        {
            printf("Key contains duplicate characters\n");
            return 1;
        }
        seen[index] = 1;
    }

    // Prompt user to provide plain text
    string input = get_string("plaintext: ");

    // Encipher the input using the key
    string output = encipher(input, argv[1]);

    // Print the ciphertext back to the user
    printf("ciphertext: %s\n", output);
}

string encipher(string input, string argv)
{
    string output = malloc(strlen(input) + 1);
    // For each alphabetic character, determine what letter it maps to
    // Preserve the case of the text that user prompted
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isalpha(input[i]))
        {
            if (isupper(input[i]))
            {
                // Map the characters of input form 0 - 25
                int p = input[i] - 'A';
                output[i] = toupper(argv[p]);
            }
            else if (islower(input[i]))
            {
                // Map the characters of input form 0 - 25
                int p = input[i] - 'a';
                output[i] = tolower(argv[p]);
            }
        }
        else
        {
            // Leave non-alphabetic characters as-is
            output[i] = input[i];
        }
    }
    output[strlen(input)] = '\0';
    return output;
}
