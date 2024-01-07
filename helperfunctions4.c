#include "main.h"
#include <stdio.h>
#include <string.h>

Alias aliases[MAX_ALIASES];
int alias_count = 0;

/**
 * print_aliases - Prints all defined aliases
 */
void print_aliases()
{
    int i;
    for (i = 0; i < alias_count; i++)
    {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

/**
 * print_alias - Prints the value of a specific alias
 * @name: The name of the alias to be printed
 */
void print_alias(const char *name)
{
    int i;
    for (i = 0; i < alias_count; i++)
    {
        if (strcmp(aliases[i].name, name) == 0)
        {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
        }
    }
}

/**
 * define_alias - Defines a new alias or updates an existing one
 * @name: The name of the alias to be defined or updated
 * @value: The value of the alias
 */
void define_alias(const char *name, const char *value)
{
    int existing_alias_index = -1;
    int i;
    for (i = 0; i < alias_count; i++)
    {
        if (strcmp(aliases[i].name, name) == 0)
        {
            existing_alias_index = i;
            break;
        }
    }
    if (existing_alias_index != -1)
    {
        strcpy(aliases[existing_alias_index].value, value);
    }
    else
    {
        if (alias_count < MAX_ALIASES)
        {
            strcpy(aliases[alias_count].name, name);
            strcpy(aliases[alias_count].value, value);
            alias_count++;
        }
        else
        {
            fprintf(stderr, "Max number of aliases reached\n");
        }
    }
}