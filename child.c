/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:06:22 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/18 18:14:14 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parse_execute(t_data *data, char **env)
{
	if (!parse(data, env))
		(recover_fd(data->backup_fd), exit(EXIT_FAILURE));
	close_pipe(data->backup_fd);
	if (execve(data->cmd_list[0], data->cmd_list, env) == -1)
	{
		p_error(NULL);
		free_2d_arr(data->cmd_list);
		recover_fd(data->backup_fd);
		exit(EXIT_FAILURE);
	}
}

void	first_child(t_data *data, int pipe_fd[2], char **env)
{
	data->id = fork();
	if (data->id == -1)
		(p_error(NULL));
	if (data->id == 0)
	{
		if (!init_backup_fd(data->backup_fd))
			(close_pipe(pipe_fd), exit(EXIT_FAILURE));
		if (!infile_config(data->file_name, pipe_fd))
			(recover_fd(data->backup_fd), exit(EXIT_FAILURE));
		parse_execute(data, env);
	}
}

void	second_child(t_data *data, int pipe_fd[2], char **env)
{
	data->id = fork();
	if (data->id == -1)
		(p_error(NULL));
	if (data->id == 0)
	{
		if (!init_backup_fd(data->backup_fd))
			(close_pipe(pipe_fd), exit(EXIT_FAILURE));
		if (!outfile_config(data->file_name, pipe_fd))
			(recover_fd(data->backup_fd), exit(EXIT_FAILURE));
		parse_execute(data, env);
	}
}
