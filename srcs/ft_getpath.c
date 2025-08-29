/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 05:57:39 by marvin            #+#    #+#             */
/*   Updated: 2025/08/29 11:20:55 by marvin           ###   ########.fr       */
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
	int		i;
	char	*curpath;
	char	**paths;

	i = 0;
	if (envp == NULL)
		return (_get_null_path());
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], PATH_PREFIX, ft_strlen(PATH_PREFIX)) != NULL)
		{
			curpath = ft_strtrim(envp[i], PATH_PREFIX);
			paths = ft_split(curpath, PATH_DELIM);
			if (curpath != NULL)
				free(curpath);
			return (paths);
		}
		i++;
	}
	return (_get_null_path());
}
