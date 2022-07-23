#include <cs50.h>
#include <stdio.h>

float discount(float price, int percentage);

int main(void)
{
    //collect initial price
    float regular = get_float("Regular Price is: ");
    //collect discount percent as whole number
    int percent_off = get_int("Percent Off: ");
    //collect final(sale) price by calling discount function
    float sale = discount(regular, percent_off);
    //print the final(sale) price
    printf("Sale Price: %.2f\n", sale);
}
    //determine the final(sale) price
float discount(float price, int percentage)
{
    return price * (100 - percentage) / 100;
}