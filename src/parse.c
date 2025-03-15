/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:44:51 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/15 21:11:37 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_2d_arr(char **arr)
{
	while (*arr)
	{
		ft_printf("%s\n", *arr);
		arr++;
	}
}

char	**extract_env_list(char **env)
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

static char	*generate_path(t_data *data, char **cmd, char **env)
{
	char	*path;
	char	*tmp;
	int		i;

	data->envp = extract_env_list(env);
	if (!data->envp)
		(ft_printf("pipex: %s: command not found\n", cmd[0]), \
		free_2d_array(cmd), exit(EXIT_FAILURE));
	i = -1;
	while (data->envp[++i])
	{
		path = ft_strjoin(data->envp[i], "/");
		if (!path)
			return (free_2d_array(data->envp), p_error(), NULL);
		tmp = path;
		path = ft_strjoin(path, cmd[0]);
		free(tmp);
		if (!path)
			return (free_2d_array(data->envp), p_error(), NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (free_2d_array(data->envp), NULL);
}

int	trim_single_quote(char **cmd_lst)
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

char	**parse_command(t_data *data, char **env)
{
	char	**cmd_list;
	char	*path;

	cmd_list = ft_split2(data->cmd);
	if (!cmd_list)
		(p_error(), exit(EXIT_FAILURE));
	if (!cmd_list[0])
		(ft_printf("pipex: %s: command not found\n", data->cmd), \
		free_2d_array(cmd_list), exit(EXIT_FAILURE));
	if (!trim_single_quote(cmd_list))
		(p_error(), free_2d_array(cmd_list), \
		exit(EXIT_FAILURE));
	if ((cmd_list[0][0] == '.' || cmd_list[0][0] == '/' ) \
	&& access(cmd_list[0], X_OK) == 0)
		return (cmd_list);
	if (ft_strchar(cmd_list[0], '/'))
		return (ft_printf("pipex : %s: no such file or directory\n", \
		cmd_list[0]), free_2d_array(cmd_list), NULL);
	path = generate_path(data, cmd_list, env);
	if (!path)
		return (ft_printf("pipex : %s: command not found\n", \
		cmd_list[0]), free_2d_array(cmd_list), NULL);
	free(cmd_list[0]);
	cmd_list[0] = path;
	return (cmd_list);
}
