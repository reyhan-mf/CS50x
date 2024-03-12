#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    bool passed = false;
    if ((argc > 2 || argc == 1))
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }
    else if (argc == 2)
    {
        if ((!(atoi(argv[1]))))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {

            for (int i = 0; i < strlen(argv[1]); i++)
            {
                    if (!atoi(&argv[1][i]))
                {
                    printf("Usage: ./caesar key\n");
                    return 1;
                }
            }
        }


    }

    int k = (atoi(argv[1]));
    string p = get_string("plaintext: ");

    // printf("%c \n", p[0]);
printf("ciphertext: ");
    for(int i = 0; i < strlen(p); i++)
    {
       if(isalpha(p[i]))
       {
            if(isupper(p[i]))
            {
                int p_out= (p[i] - 65 + k) % 26;
                printf("%c", p_out + 65);

            }
            else
            {
                int p_out= (p[i] - 97 + k) % 26;
                printf("%c", p_out + 97);

            }

       }
       else
       {
            printf("%c", p[i]);
       }
    }
printf("\n");

}
