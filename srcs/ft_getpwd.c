/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 06:12:54 by marvin            #+#    #+#             */
/*   Updated: 2025/08/30 06:29:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PWD_PREFIX "PWD="

char	*ft_getpwd(char **envp)
{
	char	*pwd;

	if (envp == NULL)
		return (NULL);
	pwd = ft_getenv(PWD_PREFIX, envp);
	if (pwd == NULL)
		return (NULL);
	return (pwd);
}
