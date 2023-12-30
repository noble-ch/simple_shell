#include "main.h"
#include <stdio.h>
#include <string.h>

Alias aliases[MAX_ALIASES];
int alias_count = 0;

void print_aliases()
{
    for (int i = 0; i < alias_count; i++)
    {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void print_alias(const char *name)
{
    for (int i = 0; i < alias_count; i++)
    {
        if (strcmp(aliases[i].name, name) == 0)
        {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
        }
    }
}

void define_alias(const char *name, const char *value)
{
    int existing_alias_index = -1;
    for (int i = 0; i < alias_count; i++)
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

