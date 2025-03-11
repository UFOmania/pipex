/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:04:15 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/11 05:16:21 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int pipe_fd[2])
{
	(close(pipe_fd[0]), close(pipe_fd[1]));
}

int	config_pipe(int pipe_fd[2], char *file_name, int flags, int index)
{
	int	new_fd;

	new_fd = open(file_name, flags, 0640);
	if (new_fd == -1)
		return (p_error(), 0);
	if (index == 1)
	{
		if (dup2(new_fd, 0) == -1)
			return (p_error(), close_pipe(pipe_fd), close(new_fd), 0);
		if (dup2(pipe_fd[1], 1) == -1)
			return (p_error(), close_pipe(pipe_fd), close(new_fd), 0);
		(close (new_fd), close_pipe (pipe_fd));
	}
	else if (index == 2)
	{
		if (dup2(pipe_fd[0], 0) == -1)
			return (p_error(), close_pipe(pipe_fd), close(new_fd), 0);
		if (dup2(new_fd, 1) == -1)
			return (p_error(), close_pipe(pipe_fd), close(new_fd), 0);
		(close(new_fd), close_pipe(pipe_fd));
	}
	return (1);
}

void	execute(t_data *data, char **env, int pipe_fd[2])
{
	char	**parsed_cmd;
	int		flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (data->index == 1)
		flags = O_RDONLY;
	data->id = fork();
	if (data->id == -1)
		(p_error(), exit(EXIT_FAILURE));
	else if (data->id == 0)
	{
		if (!config_pipe(pipe_fd, data->file_name, flags, data->index))
			exit(EXIT_FAILURE);
		parsed_cmd = parse_command(data->cmd, env);
		if (!parsed_cmd)
			(exit(EXIT_FAILURE));
		execve(parsed_cmd[0], parsed_cmd, 0);
		p_error();
		free_2d_array(parsed_cmd, 0);
		exit(EXIT_FAILURE);
	}
}

t_data	fill_data(char *file_name, char *cmd, int flag)
{
	t_data	data;

	data.file_name = file_name;
	data.cmd = cmd;
	data.index = flag;
	data.state = 0;
	data.id = 0;
	return (data);
}

// void	f(){system("leaks pipex");}

int	main(int ac, char **av, char **env)
{
	t_data	data[2];
	int		pipe_fd[2];

	data[0] = fill_data(av[1], av[2], 1);
	data[1] = fill_data(av[4], av[3], 2);
	if (ac != 5)
		return (ft_putendl_fd("Error: argument count must be 5", 2), 1);
	if (pipe(pipe_fd) == -1)
		p_error();
	execute(&data[0], env, pipe_fd);
	execute(&data[1], env, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(data[1].id, &data[1].state, 0);
	while (wait(NULL) > 0)
		;
	exit (WEXITSTATUS(data[1].state));
}

/*
char **clean_cmd(char **cmd)
{
	char	**new_cmd;
	int		i;

	i = -1;
	while (cmd[++i])
		;
	new_cmd = malloc(sizeof(char *) * (i + 1));
	if (!new_cmd)
		return (free_cmd(cmd), NULL);
	i = -1;
	while (cmd[++i])
	{
		new_cmd[i] = ft_strtrim(cmd[i], "'");
		if (!new_cmd[i])
		{
			while (i >= 0)
				free(cmd[i--]);
			free(new_cmd);	
		}
	}
	free_cmd(cmd);
	new_cmd[i] = NULL;
	return (new_cmd);
}

int	get_path_index(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH=", 5))
			return (i);
	return (-1);
}
char	*generate_path(char *cmd, char **env)
{
	char	**paths;
	int		index;
	int		j;
	char	*cmd_path;
	char	*tmp;

	index = get_path_index(env);
	if (index == -1)
		return (ft_printf("pipex: error: path is unseted\n"), free(cmd), NULL);
	paths = ft_split(env[index], ':');
	if (!paths)
		return (ft_printf("pipex: error: %s\n", strerror(errno)), free(cmd), NULL);
	j = -1;
	while (paths[++j])
	{
		tmp = ft_strjoin(paths[j], "/");
		if (!tmp)
			return (free_cmd(paths), free(cmd), ft_printf("pipex: error: %s\n", strerror(errno)), NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
			return (free_cmd(paths), free(cmd), ft_printf("pipex: error: %s\n", strerror(errno)), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (free_cmd(paths), cmd_path);
		free(cmd_path);
	}
	
	return (free_cmd(paths), NULL);
}

char **parse_command(char *av, char **env)
{
	char	**cmd;
	int		i;

	cmd = ft_split(av, ' ');
	if (!cmd)
		return (ft_printf("pipex: error: %s\n", strerror(errno)), NULL);
	cmd = clean_cmd(cmd);
	if(!cmd)
		return (ft_printf("pipex: error: %s\n", strerror(errno)), NULL);
	if (access(cmd[0], X_OK) == 0)
	{
		i = -1;
		while (cmd[++i])
			;
		char **new_cmd_lit = malloc(sizeof(char *) * (i + 2));
		if (!new_cmd_lit)
			return (ft_printf("pipex: error: %s\n", strerror(errno)), free_cmd(cmd), NULL);
		new_cmd_lit[0] = cmd[0];
		new_cmd_lit[1] = ft_strdup(ft_strrchr(cmd[0], '/') + 1);
		if (!new_cmd_lit[1])
		{
			(free(new_cmd_lit[0]), free(new_cmd_lit)); 
			return (ft_printf("pipex: error: %s\n", strerror(errno)), free_cmd(cmd), NULL);
		}
		i = 0;
		while (cmd[++i])
			new_cmd_lit[i] = cmd[i - 1];
		new_cmd_lit[i] = NULL;
		return (new_cmd_lit);
	}
	if (ft_strchr(cmd[0], '/'))
		return (ft_printf("pipex: %s: command not found\n", cmd[0]), free_cmd(cmd),  NULL);
	cmd[0] = generate_path(cmd[0], env);
	if (!cmd[0])
	{
		i = 0;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		return (ft_printf("pipex: %s: command not found\n", cmd[0]), NULL);
	}
	return (cmd);
}
*/


