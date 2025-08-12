// Hash Table data Structure
// Basically its a array of Linked lists.
// we got 26 buckets [] like that, each corrosponds to 1 alphabet
// then we attach like a linked list to each of the bucket to store the data
// it's like lets say we got 10,000,000 sentences and meaning in it
// normally to find something in it would take a lot of time
// but since we have stored based on the first alphabet of each string, our time is reduced by 26



#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    string phrase;
    struct node *next;
} node;

node *table[26];

int hash(string phrase);

int main (void)
{
    for (int i = 0; i < 3; i ++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // Get the hash code
        int bucket = hash(phrase);
        // Just to visualize
        printf("%s Hashes to %i\n", phrase, bucket);
    }
}

int hash(string phrase)
{
    return toupper(phrase[0] - 'A');
}
