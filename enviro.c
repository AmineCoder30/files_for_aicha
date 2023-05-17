#include "shell.h"

char **envir_fn_cp(void);
void fn_to_free_envir(void);
char **fn_to_get_envir(const char *var);

/**
 * envir_fn_cp - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **envir_fn_cp(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(string_lenght(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		copy_string(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * fn_to_free_envir - Frees the the environment copy.
 */
void fn_to_free_envir(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * fn_to_get_envir - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **fn_to_get_envir(const char *var)
{
	int index, len;

	len = string_lenght(var);
	for (index = 0; environ[index]; index++)
	{
		if (ncmp_string(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
