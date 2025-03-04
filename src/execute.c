/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 03:16:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/04 17:14:50 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	read_from_file1_write_to_pipe(t_data *data)
{
	// ft_printf("r1\n");
	int	new_fd;

	close(data->fd[0]);
	new_fd = open(data->file1, O_RDONLY);
	if (new_fd == -1)
	{
		put_std_err(data->file1);
		close(data->fd[1]);
		return ;
	}
	dup2(new_fd, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
}

static void	read_from_pipe_write_to_file2(t_data *data)
{
	// ft_printf("r2\n");
	int	new_fd;

	close(data->fd[1]);
	new_fd = open(data->file2, O_RDONLY);
	if (new_fd == -1)
	{
		put_std_err(data->file2);
		close(data->fd[0]);
		return ;
	}
	dup2(data->fd[0], STDIN_FILENO);
	dup2(new_fd, STDOUT_FILENO);
}

void execute_command_1(t_data *data, char **env)
{
	if (data->id != 0)
		data->id = fork();
	read_from_file1_write_to_pipe(data);
	// ft_printf("cmd 1\n");
	if (data->id == 0)
	{
		if (data->cmd_1_path == NULL)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(data->cmd_1_args[0], 2);
			ft_putendl_fd(": command not found", 2);
			close(data->fd[1]);
			exit (EXIT_FAILURE);
		}
		execve(data->cmd_1_path, data->cmd_1_args, env);
		close(data->fd[1]);
		exit(EXIT_SUCCESS);	
	}
}

void execute_command_2(t_data *data, char **env)
{
	read_from_pipe_write_to_file2(data);
	// ft_printf("line == %s", get_next_line(data->fd[0]));
	if (data->id != 0)
		data->id = fork();
	if (data->id == 0)
	{
		if (data->cmd_2_path == NULL)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(data->cmd_2_args[0], 2);
			ft_putendl_fd(": command not found", 2);
			close(data->fd[0]);
			exit (EXIT_FAILURE);
		}
		execve(data->cmd_2_path, data->cmd_2_args, env);
		close(data->fd[0]);
		exit(EXIT_SUCCESS);	
	}
}