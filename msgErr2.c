#include "shell.h"

char *errNum_126(char **amgt);
char *errNum_127(char **amgt);

/**
 * errNum_126 - this function to Creates an error mesg.
 * @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *errNum_126(char **amgt)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = string_lenght(name) + string_lenght(hist_str) + string_lenght(amgt[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": ");
	string_concat(error, amgt[0]);
	string_concat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * errNum_127 - this function to Creates an error mesg.
* @amgt: array of amgt passed.
 * Return: return errors str.
 * amine mohamed and boukhrisss
 */
char *errNum_127(char **amgt)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = string_lenght(name) + string_lenght(hist_str) + string_lenght(amgt[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": ");
	string_concat(error, amgt[0]);
	string_concat(error, ": not found\n");

	free(hist_str);
	return (error);
}
