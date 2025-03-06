/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:50:13 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/06 01:21:37 by massrayb         ###   ########.fr       */
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

void f(){system("leaks pipex");}

int	main(int ac, char **av, char **env)
{
	// atexit(f);
	t_data	data;
	pid_t	last_pid;

	int state = 0;
	data.file1 = av[1];
	data.file2 = av[4];
	data.id = getpid();
	parse_arguments(&data, av, env);
	if (create_pipe(&data) == 0)
		return (ft_putendl_fd("pipex: error : Couldn't create the pipe", 2), 1);
	// print_args(&data);
	// execute_command_1(&data, env);
	// execute_command_2(&data, env);
	execute_command(&data, env, 1);
	close(data.fd[1]);
	execute_command(&data, env, 2);
	close(data.fd[0]);
	waitpid(data.id, &data.state, 0);
	while (wait(NULL) == -1)
		;
	clean_and_exit(&data, WEXITSTATUS(data.state));
	// return (WEXITSTATUS(data.state));
	// int new_fd;
	// if(data.id != 0)
	// 	data.id = fork();
	// if (data.id == 0)
	// {
	// 	new_fd = open(data.file1, O_RDONLY);
	// 	if (new_fd == -1)
	// 	{
	// 		put_std_err(data.file1);
	// 		return (1);	
	// 	}
	// 	dup2(new_fd, 0);
	// 	dup2(data.fd[1], 1);
	// 	if (data.cmd_1_path == NULL)
	// 	{
	// 		ft_putstr_fd("pipex: ", 2);
	// 		ft_putstr_fd(data.cmd_1_args[0], 2);
	// 		return (ft_putendl_fd(" command not found", 2), 1);
	// 	}
	// 	execve(data.cmd_1_path, data.cmd_1_args, env);
	// 	exit(0);
	// }

	// if(data.id != 0)
	// 	data.id = fork();
	// if (data.id == 0)
	// {
	// 	new_fd = open(data.file2, O_RDWR);
	// 	if (new_fd == -1)
	// 	{
	// 		put_std_err(data.file2);
	// 		exit (EXIT_FAILURE);	
	// 	}
	// 	dup2(data.fd[0], 0);
	// 	dup2(new_fd, 1);
	// 	if (data.cmd_2_path == NULL)
	// 	{
	// 		ft_putstr_fd("pipex: ", 2);
	// 		ft_putstr_fd(data.cmd_2_args[0], 2);
	// 		ft_putendl_fd(": command not found", 2);
	// 		exit (EXIT_FAILURE);
	// 	}
	// 	if (execve(data.cmd_2_path, data.cmd_2_args, env) == -1)
	// 	{
	// 		put_std_err(NULL);
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	exit(0);
	// }
	// else
	// 	waitpid(data.id, &state, 0);
	
	// if (state != 0)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	// ft_printf("%s", get_next_line(data.fd[0]));
	// execve(data.cmd_1_path, data.cmd_1_args, env);

	// new_fd = open(data.file2, O_RDWR);
	// if (new_fd == -1)
	// {
	// 	ft_printf("-1\n");
	// 	put_std_err();
	// 	return (1);	
	// }
	// dup2(data.fd[0], 0);
	// dup2(new_fd, 1);

	// execve(data.cmd_2_path, data.cmd_2_args, env);
	// execute_command(&data, env);
}
