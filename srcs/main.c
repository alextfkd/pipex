/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:58:08 by tkatsuma          #+#    #+#             */
/*   Updated: 2025/09/19 07:49:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>

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

#define FT_INVALIDPATH -4
#define FT_NOTFOUND -3
#define FT_UNREADABLE -1
#define FT_UNWRITABLE -2
#define FT_READABLE 1
#define FT_WRITABLE 2

int	infile_check(char *path)
{
	if (path == NULL)
		return (-1);
	if (ft_is_posix(path) != 1)
		return (FT_INVALIDPATH);
	if (access(path, F_OK) == -1)
		return (FT_NOTFOUND);
	if (access(path, R_OK) == 0)
		return (FT_READABLE);
	return (FT_UNREADABLE);
}

int	outfile_check(char *path)
{
	if (path == NULL)
		return (-1);
	if (ft_is_posix(path) != 1)
		return (FT_INVALIDPATH);
	if (access(path, F_OK) == -1)
		return (FT_NOTFOUND);
	if (access(path, W_OK) == 0)
		return (FT_WRITABLE);
	return (FT_UNWRITABLE);
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
	// Split cmd and create argv.
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

	if (is_executable(cmd, envp) !=  X_OK)
	{
		exit (127);
	}

	// Split cmd and create argv.
	argv = ft_split(cmd, ' ');
	cmd_path = ft_which(argv[0], envp);

	// Redirect < intext
	// Redirect output.
	infild_fd = open(infile, O_RDONLY);
	if (infild_fd == -1)
	{
		free(cmd_path);
		free_argv(argv);
		exit (1);
	}
	dup2(infild_fd, STDIN_FILENO);
	close(infild_fd);

	// Redirect output
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(pipefd[1], STDERR_FILENO);
	close(pipefd[1]);

	// Execute cmd.
	execve(cmd_path, argv, envp);

	// Free if execve failed.
	//ft_printf("execve failed!!\n");
	free(cmd_path);
	free_argv(argv);

	// Return if error in execve.
	exit(0);
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

	if (is_executable(cmd, envp) !=  X_OK)
	{
		exit (127);
	}
	// Split cmd and create argv.
	argv = ft_split(cmd, ' ');
	cmd_path = ft_which(argv[0], envp);

	// Redirect < outtext
	// Open outfile and redirect outfile_fd to STDOUT_FD.
	/*
	outfile_fd = open(outfile, O_CREAT | O_RDWR);
	if (outfile_fd == -1)
		return (1);
	close(outfile_fd);
	*/
	/*
	if (access(outfile, F_OK) == 0)
		unlink(outfile);
	*/
	open(outfile, O_TRUNC);
	outfile_fd = open(outfile, O_WRONLY);
	if (outfile_fd == -1)
	{
		free(cmd_path);
		free_argv(argv);
		exit (1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	//dup2(outfile_fd, STDERR_FILENO);
	close(outfile_fd);

	execve(cmd_path, argv, envp);

	// Free if execve failed.
	free(cmd_path);
	free_argv(argv);

	exit(127);
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

	//int i;
	//i = 0;
	if (argc != 5)
		return (1);
	// Check if argv[1] is readable file.
	infile_status = infile_check(argv[1]);
	outfile_status = outfile_check(argv[4]);
	ft_printf("outfile-> %d\n", outfile_status);
	//if (outfile_status == FT_WRITABLE || outfile_status == FT_NOTFOUND)
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
		//fd = open(argv[4], O_TRUNC);
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
	/*
	if (((status1) & 0x7f) == 0)
	{
		return (((status1) & 0xff00) >> 8);
	}
	*/
	if ((waitpid(pid2, &status2, 0)) < 0)
	{
		ft_printf("error");
		return (1);
	}
	//if (((status2) & 0x7f) == 0)
	//{
	//return (127);
	return (((status2) & 0xff00) >> 8);
	//}
	
	//return (1);
}