/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 02:29:33 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/04 17:32:19 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// get the 'PATH' index from the env variables
static int get_path_index(char **env)
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
//generete the full path of the command
static char	*generate_cmd_path(char **env_paths, char *cmd)
{
	char	*full_path;
	char	*tmp;
	int		i;

	if (ft_strchr(cmd, '/') != 0)
		return (cmd);
	i = 0;
	while (env_paths[i])
	{
		tmp = ft_strjoin(env_paths[i], "/");
		if (!tmp)
			return (ft_putstr_fd("Error: ", 2), \
			ft_putendl_fd(strerror(errno), 2), NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if(!full_path)
			return (ft_putstr_fd("Error: ", 2), \
			ft_putendl_fd(strerror(errno), 2), NULL);
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

	i = get_path_index(env);
	if (i != -1)
		return (ft_split(env[i], ':'));
	return (NULL);
}

void absolute_path(t_data *data)
{
	char	*path;

	path = data->cmd_1_args[0];
	data->cmd_1_path = path;
	data->cmd_1_args[0] = ft_strdup(ft_strrchr(path, '/') + 1);
	if (data->cmd_1_args[0] == NULL)
	{
		//failed
		put_std_err(NULL);
		exit (EXIT_FAILURE);
	}
}

//parse commands arguments
void parse_arguments(t_data *data, char **av, char **env)
{
	char **env_paths;

	env_paths = get_paths(env);
	if (env_paths == NULL)
		ft_putendl_fd(ENV_NOT_FOUND, 2);
	
	data->cmd_1_args = ft_split(av[CMD_1], ' ');
	if (data->cmd_1_args[0][0] == '/')
		absolute_path(data);
	else
		data->cmd_1_path = generate_cmd_path(env_paths, data->cmd_1_args[0]);
	
	data->cmd_2_args = ft_split(av[CMD_2], ' ');
	if (data->cmd_2_args[0][0] == '/')
		absolute_path(data);
	else
		data->cmd_2_path = generate_cmd_path(env_paths, data->cmd_2_args[0]);
	data->cmd_2_path = generate_cmd_path(env_paths, data->cmd_2_args[0]);
}

