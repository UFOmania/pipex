/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 03:16:27 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/07 01:50:18 by massrayb         ###   ########.fr       */
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

static void	check_open_result(t_data *data, int fd)
{
	if (fd == -1)
		(perror(NULL), clean_and_exit(data, EXIT_FAILURE));
}

void	put_cmd_not_found(char *cmd)
{
	ft_putstr_fd("pipex: ",2);
	ft_putstr_fd(cmd ,2);
	ft_putstr_fd(" : command not found\n",2);
}
void	execute_command(t_data *data, char **env, int flag)
{
	int		new_fd;

	data->id = fork();
	if (data->id == -1)
		(perror(NULL), clean_and_exit(data, EXIT_FAILURE));
	else if (data->id == 0)
	{
		if (flag == 1)
		{
			if (data->cmd_1_path == NULL || data->cmd_1[0] == ' ' || data->cmd_1[ft_strlen(data->cmd_1) - 1] == ' ')
			(put_cmd_not_found(data->cmd_1), clean_and_exit(data, EXIT_FAILURE));
			new_fd = open(data->file1, O_RDONLY, 0640);
			check_open_result(data, new_fd);
			config_pipe(data, new_fd, flag);
			execve(data->cmd_1_path, data->cmd_1_args, env);
			(put_std_err(NULL), clean_and_exit(data, EXIT_FAILURE));
		}
		else if (flag == 2)
		{
			if (data->cmd_2_path == NULL || data->cmd_2[0] == ' ' || data->cmd_2[ft_strlen(data->cmd_2) - 1] == ' ')
			(put_cmd_not_found(data->cmd_2), clean_and_exit(data, EXIT_FAILURE));
			new_fd = open(data->file2, O_CREAT | O_WRONLY | O_TRUNC, 0640);
			check_open_result(data, new_fd);
			config_pipe(data, new_fd, flag);
			execve(data->cmd_2_path, data->cmd_2_args, env);
			(put_std_err(NULL), clean_and_exit(data, EXIT_FAILURE));
		}
	}
}
