/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:08:51 by marvin            #+#    #+#             */
/*   Updated: 2025/09/19 09:26:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define SHELL_PREFIX "SHELL="

char	*ft_getshell(char **envp)
{
	char	*shell;

	if (envp == NULL)
		return (NULL);
	shell = ft_getenv(SHELL_PREFIX, envp);
	if (shell == NULL)
		return (NULL);
	return (shell);
}
