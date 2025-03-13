/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:12:35 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/13 19:45:55 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../_libft/libft.h"
# include "../_printf/ft_printf.h"
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_data
{
	char	*file_name;
	char	*cmd;
	int		state;
	int		index;
	int		id;

}			t_data;

void	close_pipe(int pipe_fd[2]);
void	free_2d_array(char **arr, int len);
char	**parse_command(char *single_line, char **env);
void	p_error(void);

#endif