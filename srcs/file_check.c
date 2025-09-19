/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 08:55:45 by marvin            #+#    #+#             */
/*   Updated: 2025/09/19 08:56:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	infile_check(char *path)
{
	if (path == NULL)
		return (-1);
	if (ft_is_posix(path) != 1)
		return (FT_INVALIDPATH);
	if (access(path, F_OK) == -1)
		return (FT_NOTFOUND);
	if (access(path, R_OK) == 0)
		return (FT_READABLE);
	return (FT_UNREADABLE);
}

int	outfile_check(char *path)
{
	if (path == NULL)
		return (-1);
	if (ft_is_posix(path) != 1)
		return (FT_INVALIDPATH);
	if (access(path, F_OK) == -1)
		return (FT_NOTFOUND);
	if (access(path, W_OK) == 0)
		return (FT_WRITABLE);
	return (FT_UNWRITABLE);
}
