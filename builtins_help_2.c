#include "shell.h"

void envirHelper(void);
void setEnvirHelper(void);
void unSetEnvirHelper(void);
void hstorHelper(void);

/**
 * envirHelper - Displays information on the shellby builtin command 'env'.
 */
void envirHelper(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, string_lenght(msg));
}

/**
 * setEnvirHelper - Displays information on the shellby builtin command 'setenv'.
 */
void setEnvirHelper(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, string_lenght(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, string_lenght(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, string_lenght(msg));
}

/**
 * unSetEnvirHelper - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void unSetEnvirHelper(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, string_lenght(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, string_lenght(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, string_lenght(msg));
}
