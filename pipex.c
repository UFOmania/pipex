/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:13:05 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/18 19:25:16 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data data[2], char **av)
{
	data[0].file_name = av[1];
	data[0].cmd = av[2];
	data[1].file_name = av[4];
	data[1].cmd = av[3];
}

int	main(int ac, char **av, char **env)
{
	t_data	data[2];
	int		pipe_fd[2];
	int		exit_state;

	if (ac != 5)
		return (ft_printf("pipex: error: enter five args\n"), 1);
	init_data(data, av);
	if (pipe(pipe_fd) == -1)
		return (p_error(NULL), 1);
	first_child(&data[0], pipe_fd, env);
	second_child(&data[1], pipe_fd, env);
	close_pipe(pipe_fd);
	waitpid(data[0].id, NULL, 0);
	waitpid(data[1].id, &exit_state, 0);
	return (WEXITSTATUS(exit_state));
}
