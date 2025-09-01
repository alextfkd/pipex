/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 05:57:39 by marvin            #+#    #+#             */
/*   Updated: 2025/08/30 06:26:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PATH_PREFIX "PATH="
#define PATH_DELIM ':'

static char	**_get_null_path(void)
{
	char	**paths;

	paths = ft_calloc(1, (sizeof(char *)));
	if (paths == NULL)
		return (NULL);
	paths[0] = NULL;
	return (paths);
}

char	**ft_getpath(char **envp)
{
	char	*curpath;
	char	**paths;

	if (envp == NULL)
		return (_get_null_path());
	curpath = ft_getenv(PATH_PREFIX, envp);
	if (curpath == NULL)
		return (_get_null_path());
	paths = ft_split(curpath, PATH_DELIM);
	if (paths == NULL)
	{
		free(curpath);
		return (_get_null_path());
	}
	return (paths);
}
