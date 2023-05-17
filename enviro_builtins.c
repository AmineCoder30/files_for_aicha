#include "shell.h"

int envir_shell(char **args, char __attribute__((__unused__)) **front);
int set_envir_shell(char **args, char __attribute__((__unused__)) **front);
int unset_envir_shell(char **args, char __attribute__((__unused__)) **front);

/**
 * envir_shell - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int envir_shell(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], string_lenght(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * set_envir_shell - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int set_envir_shell(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (func_createErr(args, -1));

	new_value = malloc(string_lenght(args[0]) + 1 + string_lenght(args[1]) + 1);
	if (!new_value)
		return (func_createErr(args, -1));
	copy_string(new_value, args[0]);
	string_concat(new_value, "=");
	string_concat(new_value, args[1]);

	env_var = fn_to_get_envir(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (func_createErr(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * unset_envir_shell - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int unset_envir_shell(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (func_createErr(args, -1));
	env_var = fn_to_get_envir(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (func_createErr(args, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
