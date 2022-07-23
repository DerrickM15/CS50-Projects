#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    printf("%p\n", &n);
    printf("%i\n", *p);

    char *s = "HI!";
    printf("%s\n", s);
}