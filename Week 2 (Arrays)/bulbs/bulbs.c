#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    string words = get_string("Message: ");
    int length = strlen(words);

    for (int i = 0; i < length; i++)
    {
        int value = words[i];
        int binaryDigits[8] = {0};
        int index = 7;

        for (int j = 0; j < 8; j++)
        {
            // reverse the value to an array
            binaryDigits[index] = value % 2;
            value = value / 2;
            index--;
        }

        for (int j = 0; j < 8; j++)
        {
            print_bulb(binaryDigits[j]);
        }

        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
