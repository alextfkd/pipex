/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:13:35 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/27 02:12:04 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/ft_printf.h"
#include "ft_printf.h"

int	ap_as_is(va_list ap, char c)
{
	char	s[2];

	(void)ap;
	s[0] = '%';
	s[1] = c;
	return (write(1, s, 2));
}

int	typehash(char c, va_list *ap)
{
	static int	(*types[128])(va_list, char);
	static int	init_flag;
	int			i;

	if (init_flag == 0)
	{
		i = 0;
		while (i < 128)
		{
			types[i] = (void *)ap_as_is;
			i++;
		}
		types['c'] = (void *)ap_putchar;
		types['s'] = (void *)ap_putstr;
		types['d'] = (void *)ap_printdecimal;
		types['i'] = (void *)ap_printdecimal;
		types['u'] = (void *)ap_printdecimal_u;
		types['x'] = (void *)ap_printbase16l;
		types['X'] = (void *)ap_printbase16u;
		types['p'] = (void *)ap_printpointerull;
		types['%'] = (void *)ap_putpercent;
		init_flag = 1;
	}
	return (types[(int)c](*ap, c));
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	const char	*fast;
	int			len;
	int			write_len;

	len = 0;
	if (format == NULL)
		return (0);
	va_start(ap, format);
	fast = format;
	while (*fast)
	{
		if (*fast == '%')
		{
			len += write(1, format, fast - format);
			write_len = typehash(*(fast++ + 1), &ap);
			if (write_len < 0)
				return (-1);
			len += write_len;
			format = fast + 1;
		}
		fast++;
	}
	len += write(1, format, fast - format);
	return (len);
}
