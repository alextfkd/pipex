/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:17:02 by marvin            #+#    #+#             */
/*   Updated: 2025/08/30 07:29:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PATH_DELIM "/"

static void	_free_paths(char **paths)
{
	int	i;

	if (paths == NULL)
		return ;
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free (paths);
	return ;
}

static char	*_get_pwd_cmd(char *slash_cmd, char **envp)
{
	char	*pwd;
	char	*cmd_path;

	if (slash_cmd == NULL || envp == NULL)
		return (NULL);
	pwd = ft_getpwd(envp);
	cmd_path = ft_strjoin(pwd, slash_cmd);
	free(pwd);
	if (cmd_path == NULL || (access(cmd_path, X_OK) == 0))
		return (cmd_path);
	return (NULL);
}

static char	*_get_path_cmd(char *slash_cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	if (slash_cmd == NULL || envp == NULL)
		return (NULL);
	paths = ft_getpath(envp);
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = ft_strjoin(paths[i++], slash_cmd);
		if (cmd_path == NULL || (access(cmd_path, X_OK) == 0))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	_free_paths(paths);
	return (cmd_path);
}

char	*ft_which(char *cmd, char **envp)
{
	char	*slash_cmd;
	char	*cmd_path;

	if (cmd == NULL || envp == NULL)
		return (NULL);
	slash_cmd = ft_strjoin(PATH_DELIM, cmd);
	if (slash_cmd == NULL)
		return (NULL);
	cmd_path = _get_pwd_cmd(slash_cmd, envp);
	if (cmd_path != NULL)
	{
		free(slash_cmd);
		return (cmd_path);
	}
	cmd_path = _get_path_cmd(slash_cmd, envp);
	free(slash_cmd);
	if (cmd_path != NULL)
		return (cmd_path);
	return (NULL);
}
