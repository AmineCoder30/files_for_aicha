#include "shell.h"

char *func_envErr(char **args);
char *errNum_1(char **args);
char *exitErr_num2(char **args);
char *changeDErr_num2(char **args);
char *syntxErr_num2(char **args);
/**
 * func_envErr - Creates an error message for envir_shell errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *func_envErr(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = string_lenght(name) + string_lenght(hist_str) + string_lenght(args[0]) + 45;
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
	string_concat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * errNum_1 - Creates an error message for set_shellVar errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *errNum_1(char **args)
{
	char *error;
	int len;

	len = string_lenght(name) + string_lenght(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	copy_string(error, "alias: ");
	string_concat(error, args[0]);
	string_concat(error, " not found\n");

	return (error);
}

/**
 * exitErr_num2 - Creates an error message for exit_shell errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *exitErr_num2(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = string_lenght(name) + string_lenght(hist_str) + string_lenght(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": exit: Illegal number: ");
	string_concat(error, args[0]);
	string_concat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * changeDErr_num2 - Creates an error message for change_fileDir errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *changeDErr_num2(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
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
	if (args[0][0] == '-')
		string_concat(error, ": cd: Illegal option ");
	else
		string_concat(error, ": cd: can't cd to ");
	string_concat(error, args[0]);
	string_concat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * syntxErr_num2 - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *syntxErr_num2(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = string_lenght(name) + string_lenght(hist_str) + string_lenght(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": Syntax error: \"");
	string_concat(error, args[0]);
	string_concat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
