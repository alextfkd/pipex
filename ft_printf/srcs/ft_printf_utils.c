/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:31:54 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/06/30 19:59:09 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
//#include "ft_printf.h"

// Return 0 when *s is NULL.
size_t	pf_strlen(const char *s)
{
	size_t		len;
	const char	*p;

	len = 0;
	if (s == NULL)
		return (len);
	p = s;
	while (*p)
	{
		p++;
		len++;
	}
	return (len);
}

int	ap_putpercent(va_list ap, char c)
{
	(void)ap;
	return (pf_putchar((int)c));
}
