#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;
    do
    {
        cents = get_int("Changed owed: ");
    } while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    int x = 0;
    if (cents >= 25)
    {
        for (int i = 25; i <= cents; i += 25)
        {
            x = x + 1;
        }
    }
    return x;
}

int calculate_dimes(int cents)
{
    int x = 0;
    if (cents >= 10)
    {
        for (int i = 10; i <= cents; i += 10)
        {
            x = x + 1;
        }
    }
    return x;
}

int calculate_nickels(int cents)
{
    int x = 0;
    if (cents >= 5)
    {
        for (int i = 5; i <= cents; i += 5)
        {
            x = x + 1;
        }
    }
    return x;
}

int calculate_pennies(int cents)
{
    int x = 0;
    if (cents >= 1)
    {
        for (int i = 1; i <= cents; i += 1)
        {
            x = x + 1;
        }
    }
    return x;
}
