/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:50:13 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/06 17:56:20 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


// void execute_cmd(char *cmd,char *file_name, int fd[2])
// {
// 	int	fd;

// 	close(fd[0]);
// 	fd = open(file_name, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		(ft_putstr_fd("Error: ", 2), ft_putendl_fd(strerror(errno), 2));
// 		return ;
// 	}
// 	dup2(fd, STDIN_FILENO);
// 	dup2(fd[1], STDOUT_FILENO);
	
// 	// execv(cmd, )
// }
void	put_std_err(char *msg)
{
	ft_putstr_fd("pipex: ", 2);
	if (msg)
	{
		ft_putendl_fd(msg, 2);
		// ft_putstr_fd(": ", 2);
	}
	// ft_putendl_fd(strerror(errno), 2);
}
int create_pipe(t_data *data)
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
	// atexit(f);
	t_data	data;

	if (ac != 5)
		return (ft_putendl_fd("pipex: Error: arguments count must be 5", 2), 1);
	data.file1 = av[1];
	data.file2 = av[4];
	data.id = getpid();
	parse_arguments(&data, av, env);
	if (create_pipe(&data) == 0)
		return (ft_putendl_fd("pipex: error : Couldn't create the pipe", 2), 1);
	execute_command(&data, env, 1);
	close(data.fd[1]);
	execute_command(&data, env, 2);
	close(data.fd[0]);
	waitpid(data.id, &data.state, 0);
	while (wait(NULL) == -1)
		;
	clean_and_exit(&data, WEXITSTATUS(data.state));
}
