#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc , char *argv[])
{
    // Create the main List
    node *list = NULL;

    // Get input from command-line
    for (int i = 1; i < argc; i++)
    {
        // Convert string argv to int
        int number = atoi(argv[i]);

        // Allocate memory for the Number user entered
        node *n = malloc(sizeof(node));
        // If no memory available, exit the program
        if (n == NULL)
        return 1;

        // Update the memory created to hold user input
        n->number = number;
        n->next = NULL;

        // now we have to update the original 'list'
        if (list == NULL)
        {
            // Put the first node 'n' in the list
            list = n;
        }
        else if (n->number > list->number)
        {
            // If the new node 'n' is smaller in number then the first node 'list'
            n->next = list;
            list = n;
        }

        // If the new node 'n' is greater than the 'list' node
        else
        {
            // Iterate over the nodes in the 'list' to see if the new node 'n' has to be
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // If the new node 'n' is the greatest
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
                // If the new node 'n' has to be somewhere in the middle
                if (n->number < ptr->next->number)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // Print the numbers
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // Free memory
    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}
