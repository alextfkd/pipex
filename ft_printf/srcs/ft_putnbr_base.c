/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 04:45:47 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/06/30 19:59:09 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
//#include "ft_printf.h"

// If error, returns 0.
static char	getcharbase(char *base_table, int base_size, int n)
{
	if (base_table == NULL)
		return (0);
	if (base_size <= 0 || n < 0 || n >= base_size)
		return (0);
	return (base_table[n % base_size]);
}

// Returns -1 if error.
static int	putnbr_base_ul(char *base_table, int base_size, unsigned long ln)
{
	int		stack_len;
	int		total_len;
	char	c;

	total_len = 0;
	if (ln == 0)
		return (0);
	stack_len = putnbr_base_ul(base_table, base_size, ln / base_size);
	if (stack_len == -1)
		return (-1);
	total_len += stack_len;
	c = getcharbase(base_table, base_size, (int)(ln % base_size));
	if (c == 0)
		return (-1);
	stack_len = pf_putchar(c);
	if (stack_len == -1)
		return (-1);
	total_len += stack_len;
	return (total_len);
}

// Returns -1 if error. total wrote length if normal.
int	ft_putnbr_base_ul(char *base_table, unsigned long ln)
{
	int	base_size;
	int	total_len;
	int	stack_len;

	total_len = 0;
	if (base_table == NULL)
		return (-1);
	if (ln == 0)
		return (pf_putchar(base_table[0]));
	base_size = pf_strlen(base_table);
	if (base_size == 0)
		return (-1);
	stack_len = putnbr_base_ul(base_table, base_size, ln);
	if (stack_len == -1)
		return (-1);
	total_len += stack_len;
	return (total_len);
}

// Returns -1 if error.
static int	putnbr_base_ull(
	char *base_table,
	int base_size,
	unsigned long long ull
)
{
	int		stack_len;
	int		total_len;
	char	c;

	total_len = 0;
	if (ull == 0)
		return (0);
	stack_len = putnbr_base_ull(base_table, base_size, ull / base_size);
	if (stack_len == -1)
		return (-1);
	total_len += stack_len;
	c = getcharbase(base_table, base_size, (int)(ull % base_size));
	if (c == 0)
		return (-1);
	stack_len = pf_putchar(c);
	if (stack_len == -1)
		return (-1);
	total_len += stack_len;
	return (total_len);
}

// Returns -1 if error. total wrote length if normal.
int	ft_putnbr_base_ull(char *base_table, unsigned long long ull)
{
	int	base_size;
	int	total_len;
	int	stack_len;

	total_len = 0;
	if (base_table == NULL)
		return (-1);
	if (ull == 0)
		return (pf_putchar(base_table[0]));
	base_size = pf_strlen(base_table);
	if (base_size == 0)
		return (-1);
	stack_len = putnbr_base_ull(base_table, base_size, ull);
	if (stack_len == -1)
		return (-1);
	total_len += stack_len;
	return (total_len);
}
