/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 03:16:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/06 17:29:30 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	config_pipe(t_data *data, int new_fd, int flag)
{
	if (flag == 1)
	{
		if (dup2(new_fd, STDIN_FILENO) == -1)
			(perror(strerror(errno)), clean_and_exit(data, EXIT_FAILURE));
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			(perror(strerror(errno)), clean_and_exit(data, EXIT_FAILURE));
		close(new_fd);
		close(data->fd[0]);
		close(data->fd[1]);
	}
	else if (flag == 2)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			(perror(strerror(errno)), clean_and_exit(data, EXIT_FAILURE));
		if (dup2(new_fd, STDOUT_FILENO) == -1)
			(perror(strerror(errno)), clean_and_exit(data, EXIT_FAILURE));
		close(new_fd);
		close(data->fd[0]);
		close(data->fd[1]);
	}
}

void	execute_command(t_data *data, char **env, int flag)
{
	int		new_fd;

	data->id = fork();
	if (data->id == -1)
		(perror(strerror(errno)), clean_and_exit(data, EXIT_FAILURE));
	else if (data->id == 0)
	{
		if (flag == 1)
		{
			new_fd = open(data->file1, O_RDONLY, 0640);
			if (new_fd == -1)
				(put_std_err(strerror(errno)), clean_and_exit(data, EXIT_FAILURE));
			config_pipe(data, new_fd, flag);
			execve(data->cmd_1_path, data->cmd_1_args, env);
			(put_std_err("Command not found"), clean_and_exit(data, EXIT_FAILURE));
		}
		else if (flag == 2)
		{
			new_fd = open(data->file2, O_CREAT | O_WRONLY | O_TRUNC, 0640);
			if (new_fd == -1)
				(put_std_err(strerror(errno)), clean_and_exit(data, EXIT_FAILURE));
			config_pipe(data, new_fd, flag);
			execve(data->cmd_2_path, data->cmd_2_args, env);
			(put_std_err("Command not found"), clean_and_exit(data, EXIT_FAILURE));
		}
	}
}
