/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:26:03 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/27 01:52:40 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
//#include "ft_printf.h"

static int	ft_putnbr_decimal(int n)
{
	unsigned long	ul;
	int				total_len;
	int				putnbr_len;

	total_len = 0;
	if (n < 0)
	{
		total_len += pf_putchar('-');
		ul = (unsigned long)((-1) * ((long) n));
	}
	else
		ul = (unsigned long) n;
	if (total_len < 0)
		return (-1);
	putnbr_len = ft_putnbr_base_ul(BASE_10, ul);
	if (putnbr_len < 0)
		return (-1);
	total_len += putnbr_len;
	return (total_len);
}

static int	ft_putnbr_decimal_u(unsigned int u)
{
	unsigned long	ul;

	ul = (unsigned long) u;
	return (ft_putnbr_base_ul(BASE_10, ul));
}

int	ap_printdecimal_u(va_list ap, char c)
{
	(void)c;
	return (ft_putnbr_decimal_u(va_arg(ap, unsigned int)));
}

int	ap_printdecimal(va_list ap, char c)
{
	(void)c;
	return (ft_putnbr_decimal(va_arg(ap, int)));
}
