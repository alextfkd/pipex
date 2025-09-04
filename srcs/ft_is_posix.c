/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_posix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:26:24 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/09/04 22:43:52 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define NAME_MAX 255
#define PATH_MAX 4096
#define EMSG_HASSPACE "HASSPACE"
#define EMSG_LONGPATH "LONGPATH"
#define EMSG_MFAIL "MFAIL"
#define EMSG_LONGNAME "LONGNAME"

static void	_free_names(char **names)
{
	int	i;

	if (names == NULL)
		return ;
	i = 0;
	while (names[i] != NULL)
		free(names[i++]);
	free (names);
}

// Returns 1 if the path has isspace() charactors.
static int	_if_hasspace(char *path)
{
	if ((ft_strchr(path, ' ') != NULL)
		|| (ft_strchr(path, '\t') != NULL)
		|| (ft_strchr(path, '\n') != NULL)
		|| (ft_strchr(path, '\r') != NULL)
		|| (ft_strchr(path, '\f') != NULL)
		|| (ft_strchr(path, '\v') != NULL)
	)
		return (perror(EMSG_HASSPACE), 1);
	return (0);
}

// Returns 1 if the path and each filenames has
// valid names.
static int	_if_valid_length(char *path)
{
	char	**names;
	int		i;

	if (ft_strlen(path) >= PATH_MAX)
		return (perror(EMSG_LONGPATH), 0);
	names = ft_split(path, '/');
	if (names == NULL)
		return (perror(EMSG_MFAIL), 0);
	i = 0;
	while (names[i] != NULL)
	{
		if (ft_strlen(names[i++]) >= NAME_MAX)
		{
			_free_names(names);
			return (perror(EMSG_LONGNAME), 0);
		}
	}
	_free_names(names);
	return (1);
}

int	_if_posix_standard(char *path)
{
	int		res;

	if (path == NULL)
		return (-1);
	if (_if_hasspace(path) != 0)
		return (0);
	if (_is_valid_length(path) == 0)
		return (0);
	return (1);
}
