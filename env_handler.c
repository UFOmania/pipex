/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:06:10 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/17 01:11:09 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**extract_paths(char **env)
{
	int		i;
	char	**env_list;

	env_list = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			env_list = ft_split(env[i] + 5, ':');
			break ;
		}
	}
	if (env_list && !env_list[0])
		return (free(env_list), NULL);
	return (env_list);
}
