/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:58:08 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/09/19 10:00:43 by marvin           ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int		status1;
	int		status2;
	int		pid1;
	int		pid2;
	int		pipefd[2];
	int		infile_status;
	int		outfile_status;

	if (argc != 5)
		return (1);
	infile_status = infile_check(argv[1]);
	outfile_status = outfile_check(argv[4]);
	if (outfile_status == FT_WRITABLE || outfile_status == FT_NOTFOUND)
	{
		int	unlink_res;
		if (outfile_status == FT_WRITABLE)
		{
			unlink_res = unlink(argv[4]);
		}
		if (unlink_res == -1)
		{
			exit(1);
		}
		int	fd;
		fd = open(argv[4], O_CREAT);
		if (fd == -1)
			exit (1);
		close(fd);
		outfile_status = FT_WRITABLE;
	}

	if (pipe(pipefd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0 && infile_status == FT_READABLE)
		child_process_1(argv[1], argv[2], pipefd, envp);
	else if (pid1 == 0 && infile_status != FT_READABLE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0 && outfile_status == FT_WRITABLE)
		child_process_2(argv[4], argv[3], pipefd, envp);
	else if (pid2 == 0 && outfile_status != FT_WRITABLE)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if ((waitpid(pid1, &status1, 0)) < 0)
	{
		ft_printf("error");
		return (1);
	}
	if ((waitpid(pid2, &status2, 0)) < 0)
	{
		ft_printf("error");
		return (1);
	}
	return (((status2) & 0xff00) >> 8);
}