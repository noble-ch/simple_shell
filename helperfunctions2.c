#include "main.h"
/**
 *concat - copy string value in concat
 *@destination: character value
 *@source: chararcter value
 *Return: destination
 *
 */

char *concat(char *destination, char *source)
{
	int dest = 0;
	int src = 0;

	while (destination[dest] != '\0')
	{
		dest++;
	}
	while (source[src] != '\0')
	{
		destination[dest] = source[src];
		dest++;
		src++;
	}
	destination[dest] = '\0';
	return (destination);
}

/**
 * comp_strval - compare the values of a string
 * @str1: string char first
 * @str2: strinng char second
 * Return: 0
 */

int comp_strval(char *str1, char *str2)
{
	int a;

	for (a = 0; str1[a] != '\0' && str2[a] != '\0'; a++)
	{
		if (str1[a] != str2[a])
			return ((int)str1[a] - str2[a]);
	}
	return (0);
}

/**
 * string_len - copies the string pointed to by source into destination
 * @s: A pointer
 * Return: char pointer to destination
 */

int string_len(char *s)
{
	int ch = 0;

	while (*(s + ch) != '\0')
	{
		ch++;
	}

	return (ch);
}

/**
 *comp_string -  function that compares two strings.
 *@str1: string one
 *@str2: string two
 *@n: number of characters
 * Return: diference
 */

size_t comp_string(char *str1, char *str2, size_t n)
{
	size_t i, j;

	for (j = 0; str1[j] != '\0' && j < n; j++)
	{
		i = str1[j] - str2[j];

		if (i != 0)
		{
			return (i);
		}
	}
	return (0);
}

/**
 * string_copy - copies the string pointed to by source into destination
 * @destination: destination of the copy
 * @source: source of the copy
 *
 * Return: char pointer to destination
 */

char *string_copy(char *destination, char *source)
{
	int i = 0;

	while (*(source + i) != '\0')
	{
		*(destination + i) = *(source + i);
		++i;
	}
	*(destination + i) = *(source + i);

	return (destination);
}
