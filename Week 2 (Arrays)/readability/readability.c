#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float letter_len(string text);
float word_len(string text);
float sentence_len(string text);

int main(void)
{
    string text = get_string("Text: ");
    // printf("Letters: %f\n", letter_len(text));
    //  printf("word: %f\n", word_len(text));
    //  printf("sentence: %f\n", sentence_len(text));
    float L = (letter_len(text) / word_len(text)) * 100;
    // printf("L: %f\n", (L));
    float S = (sentence_len(text) / word_len(text)) * 100;
    // printf("S: %f\n", (S));
    float result = 0.0588 * L - 0.296 * S - 15.8;
    printf("%i\n  ", (int)round(result));
    if (result < 2)
    {
        printf("Before Grade 1\n");
    }
    else if (result >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(result));
    }
}

float letter_len(string text)
{
    int x = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            x++;
        }
    }
    return x;
}

float word_len(string text)
{
    int word = 1;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            word++;
        }
    }
    return word;
}

float sentence_len(string text)
{
    int word = 0;
    int length = strlen(text);
    bool punctuationSeen = false;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '?' || text[i] == '.' || text[i] == '!')
        {
            if (!punctuationSeen)
            {
                word++;
                punctuationSeen = true;
            }
        }
        else
        {
            punctuationSeen = false;
        }
    }
    return word;
}



import re
from math import round

def letter_len(text):
    return len([char for char in text if char.isalpha()])

def word_len(text):
    return len(text.split())

def sentence_len(text):
    return len(re.findall(r'[.!?]+', text))

def main():
    text = input("Text: ")
    L = (letter_len(text) / word_len(text)) * 100
    S = (sentence_len(text) / word_len(text)) * 100
    result = 0.0588 * L - 0.296 * S - 15.8
    print(f"{round(result)}")

    if result < 2:
        print("Before Grade 1")
    elif result >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(result)}")

if __name__ == "__main__":
    main()

