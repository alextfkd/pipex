/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:17:02 by marvin            #+#    #+#             */
/*   Updated: 2025/08/29 14:27:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_which(char *cmd, char **envp)
{
	int		i;
	char	*slash_cmd;
	char	**paths;
	char	*cmd_path;

	i = 0;
	if (cmd == NULL || envp == NULL)
		return (NULL);
	slash_cmd = ft_strjoin("/", cmd);
	if (slash_cmd == NULL)
		return (NULL);
	paths = ft_getpath(envp);
	while (paths[i] != NULL)
	{
		cmd_path = ft_strjoin(paths[i], slash_cmd);
		if (cmd_path == NULL)
			break ;
		if (access(cmd_path, F_OK) == 0)
			break ;
		i++;
	}
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(slash_cmd);
	return (cmd_path);
}
