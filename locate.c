#include "shell.h"

char *fill_path_dir(char *path);
lisType *direct_path(char *path);

/**
 * locate_funct - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *locate_funct(char *command)
{
	char **path, *temp;
	lisType *dirs, *head;
	struct stat st;

	path = fn_to_get_envir("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = direct_path(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(string_lenght(dirs->dir) + string_lenght(command) + 2);
		if (!temp)
			return (NULL);

		copy_string(temp, dirs->dir);
		string_concat(temp, "/");
		string_concat(temp, command);

		if (stat(temp, &st) == 0)
		{
			func_freeList(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	func_freeList(head);

	return (NULL);
}

/**
 * fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(fn_to_get_envir("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += string_lenght(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				string_concat(path_copy, pwd);
				string_concat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				string_concat(path_copy, ":");
				string_concat(path_copy, pwd);
			}
			else
				string_concat(path_copy, ":");
		}
		else
		{
			str_n_concat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * direct_path - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
lisType *direct_path(char *path)
{
	int index;
	char **dirs, *path_copy;
	lisType *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = parse_funct(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			func_freeList(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
