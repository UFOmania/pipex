/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:09:08 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/17 01:11:30 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	p_error(char *msg)
{
	if (!msg)
		ft_printf("pipex: error: %s\n", strerror(errno));
	else
		ft_printf("pipex: %s: %s\n", msg, strerror(errno));
}
