#include "shell.h"

int cant_open(char *file_path);
int prFileCmd(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = string_lenght(name) + string_lenght(hist_str) + string_lenght(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	copy_string(error, name);
	string_concat(error, ": ");
	string_concat(error, hist_str);
	string_concat(error, ": Can't open ");
	string_concat(error, file_path);
	string_concat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * prFileCmd - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int prFileCmd(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		string_concat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	replace_var(&line, exe_ret);
	line_handler(&line, line_size);
	args = parse_funct(line, " ");
	free(line);
	if (!args)
		return (0);
	if (argum_checker(args) != 0)
	{
		*exe_ret = 2;
		fn_to_free_arg(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (ncmp_string(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = arguments_call(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = arguments_call(args, front, exe_ret);

	free(front);
	return (ret);
}
