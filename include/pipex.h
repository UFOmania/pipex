/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:35:57 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/07 01:24:12 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../_libft/libft.h"
# include "../_printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

# define FILE_1 1
# define FILE_2 4
# define CMD_1 2
# define CMD_2 3

# define SKIP_PATH 5
# define ENV_NOT_FOUND "pipex : sed: No such file or directory"

typedef struct s_data
{
	char	*cmd_1_path;
	char	*cmd_2_path;
	char	**cmd_1_args;
	char	**cmd_2_args;
	char	*cmd_1;
	char	*cmd_2;
	char	*file1;
	char	*file2;
	int		state;
	int		fd[2];
	int		id;
}		t_data;

void	parse_arguments(t_data *data, char **av, char **env);
char	**get_paths(char **env);
void	execute_command_1(t_data *data, char **env);
pid_t	execute_command_2(t_data *data, char **env);
void	execute_command(t_data *data, char **env, int flag);
void	put_std_err(char *msg);
void	clean_and_exit(t_data *data, int state);
#endif