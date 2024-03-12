#include <cs50.h>
#include <stdio.h>

int main()
{
    long creditCard = get_long("Credit: ");
    long tempccnum = creditCard;
    long sum = 0;
    long finalDigit;
    long allDigit;
    long finalDigitmulti;
    int totalDigit = 0;
    bool secondDigit = false;

    while (creditCard > 0) // Creditcart is not 0 from Credit /= 10
    {
        if (secondDigit == true) // Second digit checking
        {
            finalDigit = creditCard % 10; // get each digit
            int doubleDigit = 2 * finalDigit;
            if (doubleDigit > 9) // if the digit results is more than 2 digit
            {
                // 12 % 10 = 2
                while (doubleDigit != 0)
                {
                    int x = (doubleDigit % 10);
                    sum += x; // sum of each digit
                    doubleDigit /= 10;
                }
            }
            else
            {
                sum += doubleDigit; // multiply each digit's result that is not more than 2 digit
            }
        }
        else
        {
            allDigit = creditCard % 10;
            sum += allDigit; // sum all of each not second digit
        }
        secondDigit = !secondDigit;
        creditCard /= 10;
        totalDigit++;
    }

    if (totalDigit == 13 || totalDigit == 15 || totalDigit == 16)
    {
        if (sum % 10 == 0)
        {
            if ((tempccnum / 10000000000000 == 37) || (tempccnum / 10000000000000) == 34)
            {
                printf("AMEX\n");
            }
            else if ((tempccnum / 100000000000000 >= 51) && tempccnum / 100000000000000 <= 55)
            {
                printf("MASTERCARD\n");
            }
            else if (tempccnum / 1000000000000 == 4 || tempccnum / 100000000000000 == 4 || tempccnum / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
/*

*/
