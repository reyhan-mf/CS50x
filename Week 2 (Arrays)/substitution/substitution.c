#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool checkDouble(string key);
bool checkAlphabet(string key);

int main(int argc, string argv[])
{
    bool doubled = false;

    if ((argc > 2 || argc == 1))
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }
    else if(checkAlphabet(argv[1]))
    {
        printf("Special characters are not allowed.\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26 )
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    else if (checkDouble(argv[1]))
    {
        printf("Key must not contain repeated characters");
        return 1;
    }
    else
    {
        printf("%i", checkAlphabet(argv[1]));
        string cipher = argv[1];
        string p = get_string("plaintext: ");
        char lower_all[26];
        printf("ciphertext: ");
        for (int i = 0; i < 26; i++)
        {
            lower_all[i] = tolower(cipher[i]);
        }

        for (int i = 0; i < strlen(p); i++)
        {
            if (isalpha(p[i]))
            {
                if (islower(p[i]))
                {
                    printf("%C", lower_all[p[i] - 'a']);
                }
                else
                {
                    printf("%c", (toupper((lower_all[p[i] - 'A']))));
                }
            }
            else
            {
                printf("%c", p[i]);
            }
        }
    }
    printf("\n");
}

bool checkAlphabet(string key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            return true;
        }
    }
    return false;
}


bool checkDouble(string key)
{
    for(int i = 0; i < strlen(key); i++)
    {
        for(int j = i + 1; j < strlen(key); j++)
        {
            if(key[i] == key[j])
            {
                return true;
            }
        }
    }
    return false;
}
