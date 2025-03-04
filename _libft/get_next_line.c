/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:32:34 by massrayb          #+#    #+#             */
/*   Updated: 2025/01/03 15:36:13 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_line_size(char *str)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE && str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

int	copy_lv_to_line(char **lv, char **line)
{
	int	i;

	i = 0;
	*line = malloc(get_line_size(*lv) + 1);
	if (*line == NULL)
		return (1);
	while ((*lv)[i])
	{
		(*line)[i] = (*lv)[i];
		if ((*lv)[i] == '\n')
		{
			(*line)[i + 1] = '\0';
			save_to_left_over(lv, i + 1);
			return (1);
		}
		i++;
	}
	(*line)[i] = '\0';
	free(*lv);
	*lv = NULL;
	return (0);
}

int	init_chars(char **lv, char **line, char **buff, int fd)
{
	*line = NULL;
	if (BUFFER_SIZE > INT_MAX || BUFFER_SIZE <= 0)
		return (-1);
	*buff = malloc(BUFFER_SIZE);
	if (!*buff)
		return (-1);
	if (read(fd, NULL, 0) == -1)
	{
		free(*lv);
		*lv = NULL;
		free(*buff);
		return (-1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buff;
	static char	*left_over;
	int			size;

	if (init_chars(&left_over, &line, &buff, fd) == -1)
		return (NULL);
	while (1)
	{
		if (left_over)
		{
			if (copy_lv_to_line(&left_over, &line) == 1)
				break ;
		}
		size = read(fd, buff, BUFFER_SIZE);
		if (size == 0)
			break ;
		if (buff_to_line(&buff, &line, &left_over, size))
			break ;
	}
	free(buff);
	return (line);
}
