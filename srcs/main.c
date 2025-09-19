/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:58:08 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/09/19 22:00:05 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_1(char *infile, char *cmd, int pipefd[2], char **envp)
{
	char	*cmd_path;
	char	**argv;
	int		infild_fd;

	close(pipefd[0]);
	if (is_executable(cmd, envp) != X_OK)
		exit_with_perror(127, "command not found");
	argv = ft_split(cmd, ' ');
	cmd_path = ft_which(argv[0], envp);
	infild_fd = open(infile, O_RDONLY);
	if (infild_fd == -1)
		exit_on_error(1, infild_fd, cmd_path, argv);
	dup2(infild_fd, STDIN_FILENO);
	close(infild_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(pipefd[1], STDERR_FILENO);
	close(pipefd[1]);
	execve(cmd_path, argv, envp);
	exit_on_error(0, -1, cmd_path, argv);
}

void	child_process_2(char *outfile, char *cmd, int pipefd[2], char **envp)
{
	char	*cmd_path;
	char	**argv;
	int		outfile_fd;

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (is_executable(cmd, envp) != X_OK)
		exit_with_perror(127, "command not found");
	argv = ft_split(cmd, ' ');
	cmd_path = ft_which(argv[0], envp);
	outfile_fd = open(outfile, O_TRUNC);
	if (outfile_fd == -1)
		exit_on_error(1, outfile_fd, cmd_path, argv);
	close(outfile_fd);
	outfile_fd = open(outfile, O_WRONLY);
	if (outfile_fd == -1)
		exit_on_error(1, outfile_fd, cmd_path, argv);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	execve(cmd_path, argv, envp);
	exit_on_error(127, -1, cmd_path, argv);
}

int	file_check(int (*status)[2], char *infile, char *outfile)
{
	int		outfile_fd;
	int		unlink_res;

	unlink_res = 0;
	(*status)[0] = infile_check(infile);
	(*status)[1] = outfile_check(outfile);
	if ((*status)[1] == FT_WRITABLE || (*status)[1] == FT_NOTFOUND)
	{
		if ((*status)[1] == FT_WRITABLE)
			unlink_res = unlink(outfile);
		if (unlink_res == -1)
			exit(1);
		outfile_fd = open(outfile, O_CREAT);
		if (outfile_fd == -1)
			exit (1);
		close(outfile_fd);
		(*status)[1] = FT_WRITABLE;
	}
	return (0);
}

int	wait_and_exit(int pid1, int pid2, int *status)
{
	if ((waitpid(pid1, status, 0)) < 0)
		return (1);
	if ((waitpid(pid2, status, 0)) < 0)
		return (1);
	return (((*status) & 0xff00) >> 8);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		pid1;
	int		pid2;
	int		pipefd[2];
	int		file_status[2];

	if (argc != 5)
		return (1);
	file_check(&file_status, argv[1], argv[4]);
	if (pipe(pipefd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0 && file_status[0] == FT_READABLE)
		child_process_1(argv[1], argv[2], pipefd, envp);
	else if (pid1 == 0 && file_status[0] != FT_READABLE)
		close_pipefd(pipefd);
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0 && file_status[1] == FT_WRITABLE)
		child_process_2(argv[4], argv[3], pipefd, envp);
	close_pipefd(pipefd);
	return (wait_and_exit(pid1, pid2, &status));
}
/*
	if ((waitpid(pid1, &status, 0)) < 0)
		return (1);
	if ((waitpid(pid2, &status, 0)) < 0)
		return (1);
	return (((status) & 0xff00) >> 8);
*/
