/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 03:16:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/07 20:09:00 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	config_pipe(t_data *data, int new_fd, int flag)
{
	if (flag == 1)
	{
		if (dup2(new_fd, STDIN_FILENO) == -1)
			(put_std_err(NULL), clean_and_exit(data, EXIT_FAILURE));
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			(put_std_err(NULL), clean_and_exit(data, EXIT_FAILURE));
		close(new_fd);
		close(data->fd[0]);
		close(data->fd[1]);
	}
	else if (flag == 2)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			(put_std_err(NULL), clean_and_exit(data, EXIT_FAILURE));
		if (dup2(new_fd, STDOUT_FILENO) == -1)
			(put_std_err(NULL), clean_and_exit(data, EXIT_FAILURE));
		close(new_fd);
		close(data->fd[0]);
		close(data->fd[1]);
	}
}

static void	check_open_result(t_data *data, int fd, char *file_name)
{
	if (fd == -1)
		(put_std_err(file_name), clean_and_exit(data, EXIT_FAILURE));
}

void	put_cmd_not_found(char *cmd)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
}

void	execute_command_1(t_data *data, char **env)
{
	int		new_fd;

	data->id = fork();
	if (data->id == -1)
		(put_std_err(NULL), clean_and_exit(data, EXIT_FAILURE));
	else if (data->id == 0)
	{
		if (data->cmd_1_path == NULL)
		{
			put_cmd_not_found(data->cmd_1_args[0]);
			clean_and_exit(data, EXIT_FAILURE);
		}
		new_fd = open(data->file1, O_RDONLY, 0640);
		check_open_result(data, new_fd, data->file1);
		config_pipe(data, new_fd, 1);
		execve(data->cmd_1_path, data->cmd_1_args, env);
		(put_std_err(data->cmd_1_path), clean_and_exit(data, EXIT_FAILURE));
	}
}

void	execute_command_2(t_data *data, char **env)
{
	int		new_fd;

	data->id = fork();
	if (data->id == -1)
		(put_std_err(NULL), clean_and_exit(data, EXIT_FAILURE));
	else if (data->id == 0)
	{
		if (data->cmd_2_path == NULL)
		{
			put_cmd_not_found(data->cmd_2_args[0]);
			clean_and_exit(data, EXIT_FAILURE);
		}
		new_fd = open(data->file2, O_CREAT | O_WRONLY | O_TRUNC, 0640);
		check_open_result(data, new_fd, data->file2);
		config_pipe(data, new_fd, 2);
		execve(data->cmd_2_path, data->cmd_2_args, env);
		(put_std_err(data->cmd_2_path), clean_and_exit(data, EXIT_FAILURE));
	}
}
