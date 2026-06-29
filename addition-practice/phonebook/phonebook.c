  #include <cs50.h>
  #include <stdio.h>
  #include <string.h>

  int main(void)
  {
    // Arrays of strings
    string names[] = {"Carter", "David", "Ammar"};
    string numbers[] = {"+1-614-495-1000", "+1-619-234-1000", "+92-333-4690553"};

    // Search for name
    string name = get_string("Name: ");
    for (int i = 0, l = strlen(name); i < l; i++)
    {
        if (strcmp(names[i], name) == 0)
        {
            printf("Found %s\n", numbers[i]);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
  }

