/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:27:44 by massrayb          #+#    #+#             */
/*   Updated: 2024/12/26 21:44:42 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int			get_line_size(char *str);
int			copy_lv_to_line(char **lv, char **line);
int			buff_to_line(char **buff, char **line, char **lv, int read_size);
void		extend_line(char **line, int new_size);
char		*get_next_line(int fd);
void		save_to_left_over(char **lv, int start);

#endif