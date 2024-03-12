// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int bucket = hash(word);
    node *ptr = table[hash(word)];
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Calculate hash based on the first three characters
    if (word == NULL)
    {
        return false;
    }
    char first, second, third;
    if (strlen(word) == 1)
    {
        first = (toupper(word[0]) - 'A');
        second = 0;
        third = 0;
    }
    else if(strlen(word) == 2)
    {
        first = (toupper(word[0]) - 'A');
        second = (toupper(word[1]) - 'A');
        third = 0;
    }
    else
    {
        first = (toupper(word[0]) - 'A');
        second = (toupper(word[1]) - 'A');
        third = (toupper(word[2]) - 'A');
    }

    unsigned int bucket_position = 26 * 26 * first + 26 * second + third;
    return bucket_position % N; // Ensure the bucket position is within the table size
}

unsigned int total_words = 0;

bool load(const char *dictionary)
{
    //uint8_t b;
    FILE *source = fopen(dictionary, "r");

    char word[LENGTH + 1];
    if (source == NULL)
    {
        return false;
    }
    // Read each word in the file
    while (fscanf(source, "%s", word) != EOF)
    {
        // Add each word to the hash table
        int a = hash(word);
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, word);
        new_node->next = table[a];
        table[a] = new_node;
        total_words++;
    }

    // Close the dictionary file

    fclose(source);

    // TODO
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    // TODO
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *tmp;
    for (int i = 0; i < N - 1; i++)
    {
        cursor = table[i];
        tmp = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
