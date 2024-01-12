#include "main.h"

char *strchar(const char *str_ptr, int c);
size_t strpointer(const char *str1, const char *str2);
size_t strsegment(const char *str1, const char *str2);

/**
 * strtokenize - breaks the string str1 and terminates them.
 * Delimiter-Char of start and end
 * @str: string to tokenize
 * @delim: string with the character that delimit srt.
 * Return: str
 **/
char *strtokenize(char *str, const char *delim)
{
	static char *ptr;

	if (str)
		ptr = str;
	else if (!ptr)
		return (0);
	str = ptr + strpointer(ptr, delim);
	ptr = str + strsegment(str, delim);
	if (ptr == str)
		return (ptr = 0);
	ptr = *ptr ? *ptr = 0, ptr + 1 : 0;
	return (str);
}
/**
 * strsegment - computes the maximum initial segment
 * pointed by str1
 * string pointed by str2.
 * @str1: check strring
 * @str2: string to compare
 * Return: segment length.
 **/
size_t strsegment(const char *str1, const char *str2)
{
	size_t ret = 0;

	while (*str1)
	{
		if (strchar(str2, *str1))
			return (ret);
		str1++, ret++;
	}
	return (ret);
}
/**
 * strpointer - the maximum init segment of the str
 * pointed to by str1 consists characters from string
 * pointed to by s2.
 * @str1: first string length
 * @str2: second delm string
 * Return: segment length.
 **/
size_t strpointer(const char *str1, const char *str2)
{
	size_t ret = 0;

	while (*str1 && strchar(str2, *str1++))
		ret++;
	return (ret);
}
/**
 * strchar -  char convert
 * part of the string.
 * @str: string
 * @c: character
 * Return: a ptr to the character, or a null
 * if char not in the string.
 **/
char *strchar(const char *str, int c)
{
	while (*str != (char)c)
		if (!*str++)
			return (0);
	return ((char *)str);
}
