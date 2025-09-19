/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:30:49 by marvin            #+#    #+#             */
/*   Updated: 2025/09/19 10:10:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define	R_OK	4		/* Test for read permission.  */
# define	W_OK	2		/* Test for write permission.  */
# define	X_OK	1		/* Test for execute permission.  */
# define	F_OK	0		/* Test for existence.  */

# define FT_INVALIDPATH -4
# define FT_NOTFOUND -3
# define FT_UNREADABLE -1
# define FT_UNWRITABLE -2
# define FT_READABLE 1
# define FT_WRITABLE 2

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/types.h>

int	ft_access(const char *fname);
char	**ft_getpath(char **envp);
char	*ft_which(char *cmd, char **envp);
char	*ft_getenv(char *prefix, char **envp);
char	*ft_getpwd(char **envp);
char	*ft_getshell(char **envp);
int		ft_is_posix(char *path);
int	_if_valid_filepath(char *path);
int	is_readable(char *path);
int	is_writable(char *path);
int	is_executable(char *cmd, char **envp);
int	infile_check(char *path);
int	outfile_check(char *path);
void	free_paths(char **paths);
void	free_argv(char **argv);
void	exit_on_error(int etype, int fd, char *cmd_path, char **argv);
void	exit_with_perror(int etype, char *emsg);
#endif