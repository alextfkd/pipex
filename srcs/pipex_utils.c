/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:06 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/09/19 10:12:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
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

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return ;
	while (argv[i] != NULL)
		free (argv[i++]);
	free (argv);
	return ;
}

void	exit_on_error(int etype, int fd, char *cmd_path, char **argv)
{
	free(cmd_path);
	free_argv(argv);
	if (fd >= 0)
		close(fd);
	exit (etype);
}

void	exit_with_perror(int etype, char *emsg)
{
	perror(emsg);
	exit (etype);
}
