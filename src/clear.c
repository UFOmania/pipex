/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:03:06 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/11 01:10:11 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d_array(char **arr, int len)
{
	if (len == 0)
		while (arr[len])
			free(arr[len++]);
	else
		while (--len >= 0)
			free(arr[len]);
	free(arr);
}

void	p_error(void)
{
	ft_printf("pipex: error: %s\n", strerror(errno));
}
