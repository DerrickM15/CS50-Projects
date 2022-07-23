#include <stdio.h>
#include <cs50.h>
#include <string.h>

bool triple_tap(void);
bool fourth_times(void);

int main(void)
{
    int shots = 0;//number of shots you will take if all crits
    int count = get_int("Starting round count: ");//Starting mag size
    bool triple = triple_tap();
    bool fourth = fourth_times();
    for (int i = 0; i < count; i++)
    {
        if (i % 3 == 0 && i != 0 && triple)
        {
            printf("plus 1\n");
            count++;
        }
        if (i % 4 == 0 && i != 0 && fourth)
        {
            printf("plus 2\n");
            count += 2;
        }
        shots++;
        printf("%i\n", shots);
    }
    printf("%i\n", shots);
}

bool triple_tap(void)
{
    string answer = get_string("triple tap?(y or n): ");
        if ((strcmp(answer, "y") != 0 ) && (strcmp(answer, "n") != 0))
        {
            printf("y or n please");
        }
    if (strcmp(answer, "y") == 0)
    {
        return true;
    }
    return false;
}

bool fourth_times(void)
{
    string answer = get_string("fourth times the charm?(y or n): ");
        if ((strcmp(answer, "y") != 0 ) && (strcmp(answer, "n") != 0))
        {
            printf("y or n please");
        }
    if (strcmp(answer, "y") == 0)
    {
        return true;
    }
    return false;
}