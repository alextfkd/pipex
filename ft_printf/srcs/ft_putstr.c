/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:36:35 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/06/30 19:59:09 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
//#include "ft_printf.h"

int	ft_putstr(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (ft_putstr("(null)"));
	len = pf_strlen(s);
	return (write(1, s, len));
}

int	ap_putstr(va_list ap, char c)
{
	(void)c;
	return (ft_putstr(va_arg(ap, char *)));
}
