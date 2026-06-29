#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
} person;

int main(void)
{
    // Arrays of people
    person people[3];

    people[0].name = "Ammar";
    people[0].number = "+92-333-4690553";

    people[1].name = "Abdullah";
    people[1].number = "+92-333-4690554";

    people[2].name = "Baba Jaan";
    people[2].number = "+92-323-4452179";

    // Search The name
    string name = get_string("Name: ");
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
}

