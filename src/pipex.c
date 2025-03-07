/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:50:13 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/07 20:08:48 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_std_err(char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
}

static int	create_pipe(t_data *data)
{
	if (pipe(data->fd) == -1)
	{
		put_std_err(NULL);
		return (0);
	}
	return (1);
}

// void f(){system("leaks pipex");}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 5)
		return (ft_putendl_fd("pipex: error: arguments count must be 5", 2), 1);
	data = (t_data){0};
	data.file1 = av[FILE_1];
	data.file2 = av[FILE_2];
	parse_arguments(&data, av, env);
	if (create_pipe(&data) == 0)
		return (ft_putendl_fd("pipex: error : Couldn't create the pipe", 2), 1);
	execute_command_1(&data, env);
	execute_command_2(&data, env);
	close(data.fd[1]);
	close(data.fd[0]);
	waitpid(data.id, &data.state, 0);
	while (wait(NULL) == -1)
		;
	clean_and_exit(&data, WEXITSTATUS(data.state));
}
