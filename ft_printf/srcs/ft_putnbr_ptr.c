/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:28:12 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/27 01:53:02 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
//#include "ft_printf.h"

static int	ft_putnbr_ull_base16l(unsigned long long ull)
{
	return (ft_putnbr_base_ull(BASE_16L, ull));
}

int	ap_printpointerull(va_list ap, char c)
{
	void	*ptr;
	int		len;

	(void)c;
	ptr = va_arg(ap, void *);
	if (ptr == NULL)
		return (ft_putstr("(nil)"));
	len = ft_putstr("0x");
	len += ft_putnbr_ull_base16l((unsigned long long)ptr);
	return (len);
}
