#include "main.h"
/************function to handle format********/

/**
 * handle_print - Prints an argument based on its type
 * @frmt: Formatted string in which to print the arguments.
 * @lst: List of arguments to be printed.
 * @index: index.
 * @buffer: Buffer array to handle print.
 * @flgs: Calculates active flags
 * @wid: get width.
 * @pre: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 * author:
 * amine mohamed
 * aicha lahnite
 */
int hand_pr(const char *frmt, int *index, va_list lst, char buffer[],
	int flgs, int wid, int pre, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t frmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', unsigned_prnt}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; frmt_types[i].fmt != '\0'; i++)
		if (frmt[*index] == frmt_types[i].fmt)
			return (frmt_types[i].fn(lst, buffer, flgs, wid, pre, size));

	if (frmt_types[i].fmt == '\0')
	{
		if (frmt[*index] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (frmt[*index - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (wid)
		{
			--(*index);
			while (frmt[*index] != ' ' && frmt[*index] != '%')
				--(*index);
			if (frmt[*index] == ' ')
				--(*index);
			return (1);
		}
		unknow_len += write(1, &frmt[*index], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
