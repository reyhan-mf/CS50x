#include <cs50.h>
#include <math.h>
#include <stdio.h>

/*
    #SELF NOTES
    If you use another data types instead of integer, the year output will have a bug that the year++
    is still iterating ending with year(expected) + 1

    be careful with data types!
*/

/* #Debugging codes
    do
    {
         begin = begin + ((begin / 3 -  begin / 4));
         printf("Begin value: %i\n", begin);
         year++;
         printf("Years: %i\n", year);
    }
    while(ceil(begin) < end);
*/

int main(void)
{
    // TODO: Prompt for start size
    int year = 0;
    int begin;
    do
    {
        begin = get_int("Start size: ");
    }
    while (begin < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < begin);

    // TODO: Calculate number of years until we reach threshold
    if (end == begin)
    {
        year = 0;
    }
    else
    {
        do
        {
            begin = begin + ((begin / 3 - begin / 4));
            year++;
        }
        while (ceil(begin) < end);
    }

    // TODO: Print number of years
    printf("Years: %i\n", year);
}
