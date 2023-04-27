#include "main.h"

/*********main printf function*****/


void print_bufr(char buff[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 * author:
 * amine mohamed
 * aicha lahnite
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flgs, wid, pre, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_bufr(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_bufr(buffer, &buff_ind);
			flgs = get_flg(format, &i);
			wid = get_wid(format, &i, list);
			pre = get_pre(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = hand_pr(format, &i, list, buffer,
				flgs, wid, pre, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_bufr(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_bufr - Prints the contents of the buffer if it exist.
 * @buff: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_bufr(char buff[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buff[0], *buff_ind);

	*buff_ind = 0;
}
