/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 06:16:43 by marvin            #+#    #+#             */
/*   Updated: 2025/08/30 06:20:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char *prefix, char **envp)
{
	int		i;
	char	*env;

	i = 0;
	if (prefix == NULL || envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], prefix, ft_strlen(prefix)) != NULL)
		{
			env = ft_strtrim(envp[i], prefix);
			return (env);
		}
		i++;
	}
	return (NULL);
}
