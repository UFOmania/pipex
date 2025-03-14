/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:04:15 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/14 07:38:25 by massrayb         ###   ########.fr       */
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
		execve(parsed_cmd[0], parsed_cmd, env);
		p_error();
		free_2d_array(parsed_cmd);
		free_2d_array(env);
		exit(EXIT_FAILURE);
	}
}

t_data	fill_data(char *file_name, char *cmd, int flag, char **env)
{
	t_data	data;

	data.file_name = file_name;
	data.cmd = cmd;
	data.index = flag;
	data.state = 0;
	data.id = 0;
	data.envp = extract_env_list(env);
	return (data);
}

// void	f(){system("leaks pipex");}
// atexit(f);

int	main(int ac, char **av, char **env)
{
	t_data	data[2];
	int		pipe_fd[2];

	data[0] = fill_data(av[1], av[2], 1, env);
	data[1] = fill_data(av[4], av[3], 2, env);
	if (ac != 5)
		return (ft_putendl_fd("Error: argument count must be 5", 2), 1);
	if (pipe(pipe_fd) == -1)
		p_error();
	execute(&data[0], data->envp, pipe_fd);
	execute(&data[1], data->envp, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(data[1].id, &data[1].state, 0);
	while (wait(NULL) > 0)
		;
	exit (WEXITSTATUS(data[1].state));
}
