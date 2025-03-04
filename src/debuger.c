/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:55:04 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/03 17:59:55 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void print_args(t_data *data)
{
	int i;
	ft_printf("-------------------------------\n");
	ft_printf("| file1       :%s \n| file2       :%s\n", data->file1, data->file2);

	ft_printf("| cmd-1-path  :%s\n", data->cmd_1_path);
	ft_printf("| cmd-1-args  ");
	i = -1;
	while (data->cmd_1_args[++i])
		ft_printf(":%s", data->cmd_1_args[i]);
	ft_printf("\n");

	ft_printf("| cmd-2-path  :%s\n", data->cmd_2_path);
	ft_printf("| cmd-2-args  ");
	i = -1;
	while (data->cmd_2_args[++i])
		ft_printf(":%s", data->cmd_2_args[i]);
	ft_printf("\n");
	ft_printf("-------------------------------\n");
	
}