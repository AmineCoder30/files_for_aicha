#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3
extern char **environ;
char *name;
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct listnode
{
	char *dir;
	struct listnode *next;
} lisType;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct bltnode
{
	char *name;
	int (*f)(char **argv, char **front);
} bltnType;

/**
 * struct alsNode - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alsNode.
 */
typedef struct alsNode
{
	char *name;
	char *value;
	struct alsNode *next;
} alstype;

/* gb link... list */
alstype *aliases;

/* Main Helpers */
//+copy getline functioof
ssize_t fn_get_ln(char **lineptr, size_t *n, FILE *stream);
//+copy ofrealloc function
void *fn_reset_sz(void *ptr, unsigned int old_size, unsigned int new_size);
//+ copy of strtok function
char **parse_funct(char *line, char *delim);
//get+location function
char *locate_funct(char *command);
//get+path+dir function
lisType *direct_path(char *path);
//execute function needed
int func_exc(char **args, char **front);
//free the linked list
void func_freeList(lisType *head);
//copy of itoa function
char *_itoa(int num);

/* Input Helpers */
void line_handler(char **line, ssize_t read);
void replace_var(char **args, int *exe_ret);
char *arguments_get(char *line, int *exe_ret);
int arguments_call(char **args, char **front, int *exe_ret);
int arg_runner(char **args, char **front, int *exe_ret);
int arg_handler(int *exe_ret);
int argum_checker(char **args);
void fn_to_free_arg(char **args, char **front);
char **alias_replacement(char **args);

/* String functions */
int string_lenght(const char *s);
char *string_concat(char *dest, const char *src);
char *str_n_concat(char *dest, const char *src, size_t n);
char *copy_string(char *dest, const char *src);
char *char_string(char *s, char c);
int copy_of_spn(char *s, char *accept);
int compare_string(char *s1, char *s2);
int ncmp_string(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int exit_shell(char **args, char **front);
int envir_shell(char **args, char __attribute__((__unused__)) **front);
int set_envir_shell(char **args, char __attribute__((__unused__)) **front);
int unset_envir_shell(char **args, char __attribute__((__unused__)) **front);
int change_fileDir(char **args, char __attribute__((__unused__)) **front);
int set_shellVar(char **args, char __attribute__((__unused__)) **front);
int helper_shell(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **envir_fn_cp(void);
void fn_to_free_envir(void);
char **fn_to_get_envir(const char *var);

/* Error Handling */
int func_createErr(char **args, int err);
char *func_envErr(char **args);
char *errNum_1(char **args);
char *exitErr_num2(char **args);
char *changeDErr_num2(char **args);
char *syntxErr_num2(char **args);
char *errNum_126(char **args);
char *errNum_127(char **args);

/* Linkedlist Helpers */
alstype *add_alias_end(alstype **head, char *name, char *value);
void func_free_alsList(alstype *head);
lisType *add_node_end(lisType **head, char *dir);
void func_freeList(lisType *head);

void allHelper(void);
void alsHelper(void);
void chdirHelper(void);
void extHelper(void);
void hpHelper(void);
void envirHelper(void);
void setEnvirHelper(void);
void unSetEnvirHelper(void);
void hstorHelper(void);

int prFileCmd(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
