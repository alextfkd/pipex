/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 05:25:48 by marvin            #+#    #+#             */
/*   Updated: 2025/08/21 13:17:58jg    dwrzli                      by marvin           ###   ########.fr       */
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


//child_process_1(argv[1], argv[2])
int	child_process_1(char *infile, char *cmd, int pipefd[2], char **envp)
{
	char	*cmd_path;
	char	**argv;
	int		infild_fd;
	// Child process.
	ft_printf("START CHILD1\n");

	// Close read fd.
	close(pipefd[0]);

	// Split cmd and create argv.
	argv = ft_split(cmd, ' ');
	cmd_path = ft_which(argv[0], envp);
	ft_printf("cp1 cmd_path: %s\n", cmd_path);

	// Redirect < intext
	// Redirect output.
	infild_fd = open(infile, O_RDONLY);
	if (infild_fd == -1)
		return (1);
	dup2(infild_fd, STDIN_FILENO);
	ft_printf("START CHILD1\n");

	// Redirect output
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(pipefd[1], STDERR_FILENO);

	ft_printf("START CHILD1\n");
	// Execute cmd.
	execve(cmd_path, argv, envp);

	ft_printf("START CHILD1\n");
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
	//dup2(STDIN_FILENO, pipefd[0]);

	// Split cmd and create argv.
	argv = ft_split(cmd, ' ');
	cmd_path = ft_which(argv[0], envp);
	// Redirect < outtext
	// Open outfile and redirect outfile_fd to STDOUT_FD.
	ft_printf("START CHILD2\n");
	ft_printf("cp2 cmd_path: %s\n", cmd_path);
	outfile_fd = open(outfile, O_WRONLY);
	if (outfile_fd == -1)
		return (1);
	ft_printf("START CHILD2\n");
	//dup2(STDOUT_FILENO, outfile_fd);
	dup2(outfile_fd, STDOUT_FILENO);
	//dup2(outfile_fd, STDERR_FILENO);
	ft_printf("START CHILD2\n");
	execve(cmd_path, argv, envp);
	ft_printf("START CHILD2\n");
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;

	(void)argc;
	int	pipefd[2];
	if (pipe(pipefd) == -1)
		return (1);

	int	pid1;
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
	{
		//int	res1;
		child_process_1(argv[1], argv[2], pipefd, envp);
	}
	int	pid2;
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0)
	{
		child_process_2(argv[4], argv[3], pipefd, envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	ft_printf("waiting for pid1[%d] finish\n", pid1);
	if ((waitpid(pid1, &status, 0)) < 0)
	{
		ft_printf("error");
		return (1);
	}
	ft_printf("waiting for pid1[%d] finish\n", pid1);
	ft_printf("waiting for pid2[%d] finish\n", pid2);
	waitpid(pid2, &status, 0);
	ft_printf("waiting for pid2[%d] finish\n", pid2);
	/*
	cmd2 = ft_strdup(argv[3]);
	// validate if split_count == 0.
	outfile = ft_strdup(argv[4]);
	*/


	return (0);
}