/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:04:10 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/18 12:33:02 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "_libft/libft.h"
# include "_printf/ft_printf.h"
# include <string.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_data
{
	char	*file_name;
	char	*cmd;
	char	**cmd_list;
	pid_t	id;
	int		backup_fd[2];
}		t_data;

void	p_error(char *msg);
int		init_backup_fd(int backup_fd[2]);
void	close_pipe(int pipe_fd[2]);
int		infile_config(char *infile, int pipe_fd[2]);
int		outfile_config(char *infile, int pipe_fd[2]);
void	recover_fd(int backup_fd[2]);
char	**extract_paths(char **env);
void	free_2d_arr(char **arr);
int		init_backup_fd(int backup_fd[2]);
int		parse(t_data *data, char **env);
void	first_child(t_data *data, int pipe_fd[2], char **env);
void	second_child(t_data *data, int pipe_fd[2], char **env);

#endif