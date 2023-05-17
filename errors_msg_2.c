#include "shell.h"

char *errNum_126(char **args);
char *errNum_127(char **args);

/**
 * errNum_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *errNum_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = string_lenght(name) + string_lenght(hist_str) + string_lenght(args[0]) + 24;
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
	string_concat(error, args[0]);
	string_concat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * errNum_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *errNum_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = string_lenght(name) + string_lenght(hist_str) + string_lenght(args[0]) + 16;
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
	string_concat(error, args[0]);
	string_concat(error, ": not found\n");

	free(hist_str);
	return (error);
}
