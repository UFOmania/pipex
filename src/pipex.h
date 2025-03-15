/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:12:35 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/15 21:10:24 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../_libft/libft.h"
# include "../_printf/ft_printf.h"
# include <string.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_data
{
	char	*file_name;
	char	*cmd;
	int		state;
	int		index;
	int		id;
	char	**envp;
}			t_data;

void	close_pipe(int pipe_fd[2]);
void	free_2d_array(char **arr);
char	**extract_env_list(char **env);
char	**parse_command(t_data *data, char **env);
void	p_error(void);

#endif