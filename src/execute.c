/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 03:16:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/05 22:23:20 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	config_pipe(t_data *data, int new_fd, int flag)
{
	if (flag == 1)
	{
		if (dup2(new_fd, STDIN_FILENO) == -1)
			clean_and_exit(data, EXIT_FAILURE);
		if (dup2(data->fd[1], STDOUT_FILENO) == -1)
			clean_and_exit(data, EXIT_FAILURE);
		close(data->fd[0]);
		close(new_fd);
	}
	else if (flag == 2)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			clean_and_exit(data, EXIT_FAILURE);
		if (dup2(new_fd, STDOUT_FILENO) == -1)
			clean_and_exit(data, EXIT_FAILURE);
		close(new_fd);
		close(data->fd[1]);
	}
}

void	execute_command(t_data *data, char **env, char *cmd_path, char **cmd_args, int flag)
{
	int		new_fd;

	data->id = fork();
	if (data->id == -1)
		clean_and_exit(data, EXIT_FAILURE);
	else if (data->id == 0)
	{
		if (flag == 1)
		{
			new_fd = open(data->file1, O_RDONLY, 0640);
			if (new_fd == -1)
				clean_and_exit(data, EXIT_FAILURE);
			config_pipe(data, new_fd, flag);
		}
		else if (flag == 2)
		{
			new_fd = open(data->file2, O_CREAT | O_WRONLY | O_TRUNC, 0640);
			if (new_fd == -1)
				clean_and_exit(data, EXIT_FAILURE);
			config_pipe(data, new_fd, flag);
		}
		if (execve(cmd_path, cmd_args, env) == -1)
			clean_and_exit(data, EXIT_FAILURE);
	}
}
