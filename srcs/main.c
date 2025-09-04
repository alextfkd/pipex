/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:58:08 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/09/04 22:44:14 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>

int	split_argv(int *argc, char ***argv)
{
	char	**splitted;
	int		i;
	int		split_count;
	char	**newargv;

	splitted = ft_split((const char *)(*argv)[1], ' ');
	split_count = 1;
	i = 0;
	while (splitted[split_count - 1] != NULL)
		split_count++;
	newargv = (char **)ft_calloc(sizeof(char *), split_count + 1);
	newargv[i++] = ft_strdup((*argv)[0]);
	while (i < split_count)
	{
		newargv[i] = ft_strdup(splitted[i - 1]);
		free(splitted[i - 1]);
		i++;
	}
	free(splitted);
	*argv = newargv;
	*argc = split_count;
	return (1);
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

//child_process_1(argv[1], argv[2])
int	child_process_1(char *infile, char *cmd, int pipefd[2], char **envp)
{
	char	*cmd_path;
	char	**argv;
	int		infild_fd;
	// Child process.

	// Close read fd.
	close(pipefd[0]);

	// Split cmd and create argv.
	argv = ft_split(cmd, ' ');
	cmd_path = ft_which(argv[0], envp);

	// Redirect < intext
	// Redirect output.
	infild_fd = open(infile, O_RDONLY);
	if (infild_fd == -1)
		return (1);
	dup2(infild_fd, STDIN_FILENO);
	close(infild_fd);

	// Redirect output
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(pipefd[1], STDERR_FILENO);
	close(pipefd[1]);

	// Execute cmd.
	execve(cmd_path, argv, envp);

	// Free if execve failed.
	ft_printf("execve failed!!\n");
	free(cmd_path);
	free_argv(argv);

	// Return if error in execve.
	exit(1);
}

int	child_process_2(char *outfile, char *cmd, int pipefd[2], char **envp)
{
	char	*cmd_path;
	char	**argv;
	int		outfile_fd;
	// Close write fd.
	close(pipefd[1]);
	// Execute change STDOUT_FD & STDERR_FD to pipe input.
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);

	// Split cmd and create argv.
	argv = ft_split(cmd, ' ');
	cmd_path = ft_which(argv[0], envp);

	// Redirect < outtext
	// Open outfile and redirect outfile_fd to STDOUT_FD.
	outfile_fd = open(outfile, O_WRONLY | O_CREAT);
	if (outfile_fd == -1)
		return (1);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(outfile_fd, STDERR_FILENO);
	close(outfile_fd);

	execve(cmd_path, argv, envp);

	// Free if execve failed.
	free(cmd_path);
	free_argv(argv);

	exit(1);
}

static int	_if_abspath(char *path)
{
	if (path[0] == '/')
		return (1);
	return (0);
}

int	_if_valid_filepath(char *path)
{
	if (path == NULL)
		return (NULL);
	if (_if_posix_standard(path) == 0)
		return (NULL)
	if (_if_abspath(path) == 1)

		// Abspath.
	
	

}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		pid1;
	int		pid2;
	int		pipefd[2];

	int i;
	i = 0;
	/*
	while (envp[i] != NULL)
	{
		ft_putendl_fd(envp[i++], STDOUT_FILENO);
	}
	ft_printf("pid: -> %d\n", getgid());

	ft_printf("shell: -> %s\n", ft_getshell(envp));
	*/

	(void)argc;
	if (pipe(pipefd) == -1)
		return (1);

	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
		child_process_1(argv[1], argv[2], pipefd, envp);

	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0)
		child_process_2(argv[4], argv[3], pipefd, envp);

	close(pipefd[0]);
	close(pipefd[1]);

	if ((waitpid(pid1, &status, 0)) < 0)
	{
		ft_printf("error");
		return (1);
	}
	waitpid(pid2, &status, 0);
	return (0);
}