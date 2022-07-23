#include <cs50.h>
#include <stdio.h>

string card_brand;
int card_valid;
int card_length;
void checksum(long n);

int main(void)
{
    // collect card number form user
    long card_number = get_long("Number: ");
    checksum(card_number);

}
void checksum(long n)
{
    // each digit, removed
    int d_one = (n % 10);
    int d_two = (((n % 100) - (n % 10)) / 10);
    int d_three = (((n % 1000) - (n % 100)) / 100);
    int d_four = (((n % 10000) - (n % 1000)) / 1000);
    int d_five = (((n % 100000) - (n % 10000)) / 10000);
    int d_six = (((n % 1000000) - (n % 100000)) / 100000);
    int d_seven = (((n % 10000000) - (n % 1000000)) / 1000000);
    int d_eight = (((n % 100000000) - (n % 10000000)) / 10000000);
    int d_nine = (((n % 1000000000) - (n % 100000000)) / 100000000);
    int d_ten = (((n % 10000000000) - (n % 1000000000)) / 1000000000);
    int d_eleven = (((n % 100000000000) - (n % 10000000000)) / 10000000000);
    int d_twelve = (((n % 1000000000000) - (n % 100000000000)) / 100000000000);
    int d_thirteen = (((n % 10000000000000) - (n % 1000000000000)) / 1000000000000);
    int d_fourteen = (((n % 100000000000000) - (n % 10000000000000)) / 10000000000000);
    int d_fifteen = (((n % 1000000000000000) - (n % 100000000000000)) / 100000000000000);
    int d_sixteen = (((n % 10000000000000000) - (n % 1000000000000000)) / 1000000000000000);
    // the sum of the digits for every other card number multiplied by 2
    int multiplied_two = ((d_two * 2) % 10) + ((((d_two * 2) % 100) - ((d_two * 2) % 10)) / 10);
    int multiplied_four = ((d_four * 2) % 10) + ((((d_four * 2) % 100) - ((d_four * 2) % 10)) / 10);
    int multiplied_six = ((d_six * 2) % 10) + ((((d_six * 2) % 100) - ((d_six * 2) % 10)) / 10);
    int multiplied_eight = ((d_eight * 2) % 10) + ((((d_eight * 2) % 100) - ((d_eight * 2) % 10)) / 10);
    int multiplied_ten = ((d_ten * 2) % 10) + ((((d_ten * 2) % 100) - ((d_ten * 2) % 10)) / 10);
    int multiplied_twelve = ((d_twelve * 2) % 10) + ((((d_twelve * 2) % 100) - ((d_twelve * 2) % 10)) / 10);
    int multiplied_fourteen = ((d_fourteen * 2) % 10) + ((((d_fourteen * 2) % 100) - ((d_fourteen * 2) % 10)) / 10);
    int multiplied_sixteen = ((d_sixteen * 2) % 10) + ((((d_sixteen * 2) % 100) - ((d_sixteen * 2) % 10)) / 10);

    if (d_sixteen == 0 && d_fifteen == 0 && d_fourteen == 0)
    {
        card_length = 13;
    }
    else if (d_sixteen == 0)
    {
        card_length = 15;
    }
    else if (d_sixteen > 0)
    {
        card_length = 16;
    }

    // the sum of all of the multiplied digits
    int product = multiplied_two + multiplied_four + multiplied_six + multiplied_eight + multiplied_ten + multiplied_twelve
                  + multiplied_fourteen + multiplied_sixteen;
    // the sum of the unmultiplied digits
    int odds = d_one + d_three + d_five + d_seven + d_nine + d_eleven + d_thirteen + d_fifteen;
    //the final valid check, based on theremainder of the multiplied and unmultiplied digits
    card_valid = (product + odds) % 10;
    // if the card number is longer than 13 digits, the first digit is 4, and the card is valid
    if (((card_length == 13 && d_thirteen == 4) || (card_length == 14 && d_fourteen == 4) || (card_length == 15 && d_fifteen == 4)
         || (card_length == 16 && d_sixteen == 4))  && card_valid == 0)
    {
        printf("VISA\n");
    }
    // if the card number is 15 digits, the first digit of the card is 3, the second digit is 4 or 7, and the card is valid
    else if (card_length == 15 && d_fifteen == 3 && (d_fourteen == 4 || d_fourteen == 7) && card_valid == 0)
    {
        printf("AMEX\n");
    }
    // if first digit of the card is 5, the second digit is within 1-5, and the card is valid
    else if (d_sixteen == 5 && d_fifteen >= 1 && d_fifteen <= 5 && card_valid == 0)
    {
        printf("MASTERCARD\n");
    }
    // if no checks pass, card is invalid
    else
    {
        printf("INVALID\n");
    }
}