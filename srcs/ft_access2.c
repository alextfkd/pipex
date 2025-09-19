/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:06:50 by marvin            #+#    #+#             */
/*   Updated: 2025/09/19 09:35:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	_if_abspath(char *path)
{
	if (path[0] == '/')
		return (1);
	return (0);
}

int	_if_valid_filepath(char *path)
{
	if (path == NULL)
		return (-1);
	if (ft_is_posix(path) != 1)
		return (-1);
	if (_if_abspath(path) == 1)
		return (1);
	return (0);
}

int	is_readable(char *path)
{
	if (path == NULL)
		return (-1);
	if (ft_is_posix(path) != 1)
		return (-1);
	if (access(path, F_OK) == -1)
		return (-1);
	if (access(path, R_OK) == 0)
		return (R_OK);
	return (0);
}

int	is_writable(char *path)
{
	if (path == NULL)
		return (-1);
	if (ft_is_posix(path) != 1)
		return (-1);
	if (access(path, F_OK) == -1)
		return (W_OK);
	if (access(path, W_OK) == 0)
		return (W_OK);
	return (0);
}

int	is_executable(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**argv;
	int		res;

	if (cmd == NULL)
		return (-1);
	argv = ft_split(cmd, ' ');
	if (argv == NULL)
		return (-1);
	cmd_path = ft_which(argv[0], envp);
	if (cmd_path == NULL)
		res = -1;
	else if (ft_is_posix(cmd_path) != 1)
		res = -1;
	else if (access(cmd_path, F_OK) == -1)
		res = -1;
	else if (access(cmd_path, X_OK) == 0)
		res = X_OK;
	else
		res = 0;
	free_paths(argv);
	free(cmd_path);
	return (res);
}
