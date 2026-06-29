// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of words loaded inside the dictionary
int word_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

node *Hash_table[N];

// This function is used inside hash
int letter_to_number(char letter)
{
    return tolower(letter) - 'a';
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Return True if the word is in the dictionary and False if not
    // Check is case insensitive

    // Step 1: Hash the word to obtain a hash value
    int word_hashed_index = hash(word);

    // Step 2: Access the linked list at that hash_index
    node *cursor = Hash_table[word_hashed_index];

    // Traverse the linked list tell you get to null
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    // If the word is not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (strlen(word) < 3)
    {
        // Handle shorter words
        return 0;
    }
    else
    {
        int num1 = letter_to_number(word[0]);
        int num2 = letter_to_number(word[1]);
        int num3 = letter_to_number(word[2]);
        return 26 * 26 * num1 + 26 * num2 + num3;
    }
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // Create a temperory array of char's to store words read by fscanf
    char temp[LENGTH + 1];

    // Read each word from the file one at a time
    while (fscanf(source, "%s", temp) != EOF)
    {
        // Make new nodes to store each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        // Copy words into nodes and set the next pointer to NULL
        strcpy(new_node->word, temp);
        new_node->next = NULL;

        // Hash the word to obtain the hash value
        int hash_index = hash(new_node->word);

        // Insert that word based on its hash value into the table
        // If this is the first node
        if (Hash_table[hash_index] == NULL)
        {
            Hash_table[hash_index] = new_node;
            word_count += 1;
        }
        else
        {
            new_node->next = Hash_table[hash_index];
            Hash_table[hash_index] = new_node;
            word_count += 1;
        }
    }
    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    // Traverse the whole Hash Table
    for (int i = 0; i < N; i++)
    {
        node *cursor = Hash_table[i];
        node *temp = cursor;
        // Get into the buckets one by one
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
