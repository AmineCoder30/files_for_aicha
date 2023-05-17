#include "shell.h"

char *arguments_get(char *line, int *exe_ret);
int arguments_call(char **args, char **front, int *exe_ret);
int arg_runner(char **args, char **front, int *exe_ret);
int arg_handler(int *exe_ret);
int argum_checker(char **args);

/**
 * arguments_get - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *arguments_get(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = fn_get_ln(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (arguments_get(line, exe_ret));
	}

	line[read - 1] = '\0';
	replace_var(&line, exe_ret);
	line_handler(&line, read);

	return (line);
}

/**
 * arguments_call - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int arguments_call(char **args, char **front, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (ncmp_string(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = alias_replacement(args);
			ret = arg_runner(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (ncmp_string(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = alias_replacement(args);
			ret = arg_runner(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = alias_replacement(args);
	ret = arg_runner(args, front, exe_ret);
	return (ret);
}

/**
 * arg_runner - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int arg_runner(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = func_exc(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * arg_handler - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int arg_handler(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = arguments_get(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = parse_funct(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (argum_checker(args) != 0)
	{
		*exe_ret = 2;
		fn_to_free_arg(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (ncmp_string(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = arguments_call(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = arguments_call(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * argum_checker - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int argum_checker(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (func_createErr(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (func_createErr(&args[i + 1], 2));
		}
	}
	return (0);
}
