/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatsuma <tkatsuma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:30:49 by marvin            #+#    #+#             */
/*   Updated: 2025/09/09 18:15:25 by tkatsuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define	R_OK	4		/* Test for read permission.  */
# define	W_OK	2		/* Test for write permission.  */
# define	X_OK	1		/* Test for execute permission.  */
# define	F_OK	0		/* Test for existence.  */

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
void	free_paths(char **paths);
#endif