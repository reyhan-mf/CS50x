#include <cs50.h>
#include <stdio.h>

int main(void)
{   int n;
    do
    {
         n = get_int("Height: ");
    }
    while(n < 1 || n > 8);

    for (int i = 1; i <= n; i++)
    {

        for (int k = n; k > i; k--)
        {
            printf(" ");
        }

        for (int j = i; j > 0; j--)
        {
            printf("#");
        }

        printf(" ");

        for (int j = i; j > 0; j--)
        {
            printf("#");
        }

        printf("\n");
    }
}
