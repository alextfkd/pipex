/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ul_base16.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:22:11 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/05/27 01:53:32 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
//#include "ft_printf.h"

static int	ft_putnbr_ul_base16l(unsigned long ln)
{
	return (ft_putnbr_base_ul(BASE_16L, ln));
}

static int	ft_putnbr_ul_base16u(unsigned long ln)
{
	return (ft_putnbr_base_ul(BASE_16U, ln));
}

int	ap_printbase16l(va_list ap, char c)
{
	(void)c;
	return (ft_putnbr_ul_base16l(va_arg(ap, unsigned int)));
}

int	ap_printbase16u(va_list ap, char c)
{
	(void)c;
	return (ft_putnbr_ul_base16u(va_arg(ap, unsigned int)));
}
