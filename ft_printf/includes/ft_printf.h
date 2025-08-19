/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 22:13:30 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/06/30 19:59:09 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# define BASE_10 "0123456789"
# define BASE_16L "0123456789abcdef"
# define BASE_16U "0123456789ABCDEF"

size_t	pf_strlen(const char *s);
int		pf_putchar(int c);
int		ft_putnbr_base_ul(char *base_table, unsigned long ln);
int		ft_putnbr_base_ull(char *base_table, unsigned long long ull);

int		ap_printbase16l(va_list ap, char c);
int		ap_printbase16u(va_list ap, char c);
int		ap_printdecimal_u(va_list ap, char c);
int		ap_printdecimal(va_list ap, char c);
int		ap_printpointerull(va_list ap, char c);
int		ft_putstr(const char *s);
int		ap_putstr(va_list ap, char c);
int		pf_putchar(int c);
int		ap_putchar(va_list ap, char c);
int		ap_putpercent(va_list ap, char c);
int		ft_printf(const char *format, ...);
#endif
