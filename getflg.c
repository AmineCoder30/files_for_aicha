#include "main.h"

/**************** funcction that handle flags********************/

/**
 * get_flg - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 * author:
 * amine mohamed
 * aicha lahnite
 */
int get_flg(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, current_i;
	int flgs = 0;
	const char chane_flags[] = {'-', '+', '0', '#', ' ', '\0'};
	const int array_flags[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_i = *i + 1; format[current_i] != '\0'; current_i++)
	{
		for (j = 0; chane_flags[j] != '\0'; j++)
			if (format[current_i] == chane_flags[j])
			{
				flgs |= array_flags[j];
				break;
			}

		if (chane_flags[j] == 0)
			break;
	}

	*i = current_i - 1;

	return (flgs);
}
