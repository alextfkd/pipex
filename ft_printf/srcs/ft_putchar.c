/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:35:36 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/27 01:51:14 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
//#include "ft_printf.h"

// Returns -1 if failed.
int	pf_putchar(int c)
{
	int	len;

	len = write(1, &c, 1);
	if (len != 1)
		return (-1);
	return (len);
}

int	ap_putchar(va_list ap, char c)
{
	(void)c;
	return (pf_putchar(va_arg(ap, int)));
}
