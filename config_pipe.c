/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:13:43 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/18 19:29:35 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_backup_fd(int backup_fd[2])
{
	backup_fd[0] = dup(0);
	if (backup_fd[0] == -1)
		return (p_error(NULL), 0);
	backup_fd[1] = dup(1);
	if (backup_fd[1] == -1)
		return (p_error(NULL), close(backup_fd[0]), 0);
	return (1);
}

void	recover_fd(int backup_fd[2])
{
	if (dup2(backup_fd[0], 0) == -1)
		p_error(NULL);
	if (dup2(backup_fd[1], 1) == -1)
		p_error(NULL);
	close_pipe(backup_fd);
}

void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (p_error(NULL), 0);
	return (1);
}

int	infile_config(char *infile, int pipe_fd[2])
{
	int	new_fd;

	close(pipe_fd[0]);
	new_fd = open(infile, O_RDONLY);
	if (new_fd == -1)
		return (p_error(infile), close(pipe_fd[1]), 0);
	if (dup2(new_fd, 0) == -1)
		return (p_error(NULL), close(new_fd), close(pipe_fd[1]), 0);
	if (dup2(pipe_fd[1], 1) == -1)
		return (p_error(NULL), close(new_fd), close(pipe_fd[1]), 0);
	close(new_fd);
	close(pipe_fd[1]);
	return (1);
}

int	outfile_config(char *outfile, int pipe_fd[2])
{
	int	new_fd;

	close(pipe_fd[1]);
	new_fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (new_fd == -1)
		return (p_error(outfile), close(pipe_fd[0]), 0);
	if (dup2(new_fd, 1) == -1)
		return (p_error(NULL), close(new_fd), close(pipe_fd[0]), 0);
	if (dup2(pipe_fd[0], 0) == -1)
		return (p_error(NULL), close(new_fd), close(pipe_fd[0]), 0);
	close(new_fd);
	close(pipe_fd[0]);
	return (1);
}
