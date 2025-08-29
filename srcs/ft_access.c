/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:50:37 by marvin            #+#    #+#             */
/*   Updated: 2025/08/21 13:51:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_add_if_x_ok(const char *fname)
{
	if (access(fname, X_OK) == 0)
		return (X_OK);
	return (-1);
}

static int	_add_if_w_ok(const char *fname)
{
	if (access(fname, W_OK) == 0)
		return (W_OK);
	return (-1);
}

static int	_add_if_r_ok(const char *fname)
{
	if (access(fname, R_OK) == 0)
		return (R_OK);
	return (-1);
}

int	ft_access(const char *fname)
{
	int	permission;

	permission = 0;
	if (fname == NULL || access(fname, F_OK) == -1)
		return (-1);
	permission += _add_if_x_ok(fname);
	permission += _add_if_w_ok(fname);
	permission += _add_if_r_ok(fname);
	return (permission);
}
