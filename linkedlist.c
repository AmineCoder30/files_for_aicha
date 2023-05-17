#include "shell.h"

alstype *add_alias_end(alstype **head, char *name, char *value);
void func_free_alsList(alstype *head);
lisType *add_node_end(lisType **head, char *dir);
void func_freeList(lisType *head);

/**
 * add_alias_end - Adds a node to the end of a alstype linked list.
 * @head: A pointer to the head of the lisType list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alstype *add_alias_end(alstype **head, char *name, char *value)
{
	alstype *new_node = malloc(sizeof(alstype));
	alstype *last;

	if (!new_node)
		return (NULL);

	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (string_lenght(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	copy_string(new_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * add_node_end - Adds a node to the end of a lisType linked list.
 * @head: A pointer to the head of the lisType list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
lisType *add_node_end(lisType **head, char *dir)
{
	lisType *new_node = malloc(sizeof(lisType));
	lisType *last;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * func_free_alsList - Frees a alstype linked list.
 * @head: THe head of the alstype list.
 */
void func_free_alsList(alstype *head)
{
	alstype *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * free_list - Frees a lisType linked list.
 * @head: The head of the lisType list.
 */
void func_freeList(lisType *head)
{
	lisType *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
