/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 02:29:33 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/07 06:39:27 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	get_path_index(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_memcmp("PATH=", env[i], 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*generate_cmd_path(char **env_paths, char *cmd)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (env_paths[i])
	{
		tmp = ft_strjoin(env_paths[i], "/");
		if (!tmp)
			return (put_std_err(NULL), NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (put_std_err(NULL), NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = get_path_index(env);
	if (i != -1)
		paths = ft_split(env[i] + SKIP_PATH, ':');
	return (paths);
}

static void	handle_absolute_path(t_data *data, int flag)
{
	char	*path;

	if (flag == 1)
	{
		path = data->cmd_1_args[0];
		data->cmd_1_args[0] = ft_strdup(ft_strrchr(path, '/') + 1);
		if (data->cmd_1_args[0] == NULL)
			(put_std_err(data->cmd_1_args[0]), free(path), \
			clean_and_exit(data, EXIT_FAILURE));
		data->cmd_1_path = path;
	}
	else if (flag == 2)
	{
		path = data->cmd_2_args[0];
		data->cmd_2_args[0] = ft_strdup(ft_strrchr(path, '/') + 1);
		if (data->cmd_2_args[0] == NULL)
			(put_std_err(data->cmd_2_args[0]), free(path), \
			clean_and_exit(data, EXIT_FAILURE));
		data->cmd_2_path = path;
	}
}

void	parse_arguments(t_data *data, char **av, char **env)
{
	char	**env_paths;
	int		i;

	env_paths = get_paths(env);
	if (env_paths == NULL)
		(ft_putendl_fd(ENV_NOT_FOUND, 2), exit (1));
	data->cmd_1_args = ft_split(av[CMD_1], ' ');
	if (data->cmd_1_args[0] && data->cmd_1_args[0][0] == '/')
		handle_absolute_path(data, 1);
	else
		data->cmd_1_path = generate_cmd_path(env_paths, data->cmd_1_args[0]);
	data->cmd_2_args = ft_split(av[CMD_2], ' ');
	if (data->cmd_2_args[0] && data->cmd_2_args[0][0] == '/')
		handle_absolute_path(data, 2);
	else
		data->cmd_2_path = generate_cmd_path(env_paths, data->cmd_2_args[0]);
	i = -1;
	while (env_paths[++i])
		free(env_paths[i]);
	free(env_paths);
}
