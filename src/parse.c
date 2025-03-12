/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:44:51 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/12 21:10:29 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_2d_arr(char **arr) //
{
	while (*arr)
	{
		ft_printf("%s\n", *arr);
		arr++;
	}
}

/*
static char	**extract_cmd_from_path(char **old_cmd_list)
{
	char	**new_cmd_list;
	int		i;

	i = -1;
	while (old_cmd_list[++i])
		;
	new_cmd_list = malloc(sizeof(char *) * (i + 2));
	if (!new_cmd_list)
		return (ft_printf("pipex: error: %s\n", strerror(errno)), free_2d_array(old_cmd_list, 0), NULL);
	new_cmd_list[0] = ft_strdup(old_cmd_list[0]);
	if (!new_cmd_list[0])
		return (ft_printf("pipex: error: %s\n", strerror(errno)), free(new_cmd_list), free_2d_array(old_cmd_list, 0), NULL);
	new_cmd_list[1] = ft_strdup(ft_strrchr(old_cmd_list[0], '/') + 1);
	if (!new_cmd_list[1])
		return (ft_printf("pipex: error: %s\n", strerror(errno)),  free_2d_array(new_cmd_list, 1), free_2d_array(old_cmd_list, 0), NULL);
	i = 0;
	while (old_cmd_list[++i])
	{
		new_cmd_list[i + 1] = ft_strdup(old_cmd_list[i]);
		if (!new_cmd_list[i + 1])
			return (ft_printf("pipex: error: %s\n", strerror(errno)), free_2d_array(new_cmd_list, i + 1), free_2d_array(old_cmd_list, 0), NULL);
	}
	new_cmd_list[i + 1] = NULL;
	return ( free_2d_array(old_cmd_list, 0), new_cmd_list);
}
*/
//-----------------------------------------------



//-----------------------------------------------

static char	**extract_env_list(char **env)
{
	int		i;
	char	**env_list;
	char	*first_path;

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

static char	*generate_path(char **cmd, char **env)
{
	char	**env_list;
	char	*path;
	char	*tmp;
	int		i;

	env_list = extract_env_list(env);
	if (!env_list)
		(ft_printf("pipex: %s: command not found\n", cmd[0]), \
		free_2d_array(cmd, 0), exit(EXIT_FAILURE));
	i = -1;
	while (env_list[++i])
	{
		path = ft_strjoin(env_list[i], "/");
		if (!path)
			return (free_2d_array(env_list, 0), p_error(), NULL);
		tmp = path;
		path = ft_strjoin(path, cmd[0]);
		free(tmp);
		if (!path)
			return (free_2d_array(env_list, 0), p_error(), NULL);
		
		if (access(path, X_OK) == 0)
			return (free_2d_array(env_list, 0), path);
		free(path);
	}
	return (free_2d_array(env_list, 0), NULL);
}

int trim_single_quote(char **cmd_lst)
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

char	**parse_command(char *single_line, char **env)
{
	char	**cmd_list;
	char	*path;

	cmd_list = ft_split2(single_line);
	if (!cmd_list)
		(p_error(), exit(EXIT_FAILURE));
	if (!trim_single_quote(cmd_list))
		(free_2d_array(cmd_list, 0), p_error(), exit(EXIT_FAILURE));
	if ((cmd_list[0][0] == '.' || cmd_list[0][0] == '/' ) \
	&& access(cmd_list[0], X_OK) == 0)
		return ( cmd_list);
	if (ft_strchar(cmd_list[0], '/'))
		return (ft_printf("pipex : %s: no such file or directory\n", \
		cmd_list[0]), free_2d_array(cmd_list, 0), NULL);
	path = generate_path(cmd_list, env);
	if (!path)
		return (ft_printf("pipex : %s: command not found\n", \
		cmd_list[0]), free_2d_array(cmd_list, 0), NULL);
	free(cmd_list[0]);
	cmd_list[0] = path;
	return (cmd_list);
}

// void f(){system("leaks a.out");}

// int main(int r, char **v, char **env)
// {
// 	atexit(f);
// 	// char *argv[] = { "/bin/ls", "-l", NULL };
//     // char *envp[] = { "PATH=/usr/bin", "USER=john", NULL };
// 	char **c = parse_command("/bin/ls -l -g", env);
// 	if (!c)
// 		return (EXIT_FAILURE);
// 	int i = -1;
// 	while (c[++i])
// 		ft_printf("%s\n", c[i]);
// 	// execve(c[0], c, 0);
// 	// free_2d_array(c, 0);
// }