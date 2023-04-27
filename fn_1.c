#include "main.h"

/***************function that print insigned number****************/
/**
 * print_unsigned - Prints an unsigned number.
 * @types: List a of arguments
 * @bfr: Buffer array to handle print
 * @flgs:  Calculates active flgs
 * @wid: get width
 * @pre: pre specification
 * @size: Size specifier
 * Return: Number of chars printed.
 * author:
 * amine mohamed
 * aicha lahnite
 */
int unsigned_prnt(va_list types, char bfr[],
	int flgs, int wid, int pre, int size)
{
	int i = BUFF_SIZE - 2;

	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);


	if (num == 0)
		bfr[i--] = '0';

	bfr[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		bfr[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, bfr, flgs, wid, pre, size));
}

/************function that print unssigned number in octal ***********/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @bfr: Buffer array to handle print
 * @flgs:  Calculates active flgs
 * @wid: get width
 * @pre: pre specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char bfr[],
	int flgs, int wid, int pre, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		bfr[i--] = '0';

	bfr[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		bfr[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flgs & F_HASH && init_num != 0)
		bfr[i--] = '0';

	i++;

	return (write_unsgnd(0, i, bfr, flgs, wid, pre, size));
}

/************** fn that pr unss num in hexa **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @bfr: Buffer array to handle print
 * @flgs:  Calculates active flags
 * @wid: get width
 * @pre: pre specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char bfr[],
	int flgs, int wid, int pre, int size)
{
	return (print_hexa(types, "0123456789abcdef", bfr,
		flgs, 'x', wid, pre, size));
}

/*************fn that pr unss num in uphexa**************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @bfr: Buffer array to handle print
 * @flgs:  Calculates active flags
 * @wid: get width
 * @pre: pre specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char bfr[],
	int flgs, int wid, int pre, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", bfr,
		flgs, 'X', wid, pre, size));
}

/************** fn that pr num in uphexa and lowerhex **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @bfr: Buffer array to handle print
 * @flgs:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @wid: get width
 * @pre: pre specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char bfr[],
	int flgs, char flag_ch, int wid, int pre, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(wid);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		bfr[i--] = '0';

	bfr[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		bfr[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flgs & F_HASH && init_num != 0)
	{
		bfr[i--] = flag_ch;
		bfr[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, bfr, flgs, wid, pre, size));
}
