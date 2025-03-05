/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:48:13 by massrayb          #+#    #+#             */
/*   Updated: 2025/03/05 20:56:28 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void clean_and_exit(t_data *data, int state)
{
	int	i;

	// p("cleaning\n");
	// p("pa %s\n", data->cmd_1_path);
	// p("pa %s\n", data->cmd_2_path);
	free(data->cmd_1_path);
	free(data->cmd_2_path);
	i = -1;
	if (data->cmd_1_args)
		while (data->cmd_1_args[++i])
			free(data->cmd_1_args[i]);
	free(data->cmd_1_args);
	i = -1;
	if (data->cmd_2_args)
		while (data->cmd_2_args[++i])
			free(data->cmd_2_args[i]);
	free(data->cmd_2_args);
	close(data->fd[0]);
	close(data->fd[1]);
	exit (state);
}