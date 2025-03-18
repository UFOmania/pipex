/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:14:59 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/18 04:45:06 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_path(char *path)
{
	if (ft_strrchr(path, '/'))
		return (1);
	return (0);
}

static int	generate_path(char **cmd, char **env)
{
	char	**env_paths;
	char	*tmp;
	char	*path;
	int		i;

	env_paths = extract_paths(env);
	if (!env_paths)
		return (0);
	i = -1;
	while (env_paths[++i])
	{
		path = ft_strjoin(env_paths[i], "/");
		if (!path)
			return (p_error(NULL), free_2d_arr(env_paths), 0);
		tmp = path;
		path = ft_strjoin(path, *cmd);
		free(tmp);
		if (!path)
			return (p_error(NULL), free_2d_arr(env_paths), 0);
		if (access(path, X_OK) == 0)
			return (free(*cmd), *cmd = path, 1);
		free(path);
	}
	return (free_2d_arr(env_paths), 0);
}

static int	trim_single_quote(char **cmd_lst)
{
	int		i;
	char	*tmp;

	i = -1;
	while (cmd_lst[++i])
	{
		tmp = ft_strtrim(cmd_lst[i], "'");
		if (!tmp)
			return (0);
		free(cmd_lst[i]);
		cmd_lst[i] = tmp;
	}
	return (1);
}

int	parse(t_data *data, char **env)
{
	data->cmd_list = ft_split2(data->cmd);
	if (!data->cmd_list)
		(p_error(NULL), exit(EXIT_FAILURE));
	if (!trim_single_quote(data->cmd_list))
		(p_error(NULL), free_2d_arr(data->cmd_list), \
		exit(EXIT_FAILURE));
	if (is_path(data->cmd_list[0]))
	{
		if (access(data->cmd_list[0], X_OK) == -1)
			return (p_error(data->cmd_list[0]), free_2d_arr(data->cmd_list), 0);
		else
			return (1);
	}
	if (!generate_path(&data->cmd_list[0], env))
		return (ft_printf("pipex: %s: command not found\n", data->cmd_list[0]), \
		free_2d_arr(data->cmd_list), 0);
	return (1);
}
