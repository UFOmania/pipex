/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:40:32 by massrayb          #+#    #+#             */
/*   Updated: 2024/12/21 10:15:19 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strchar(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_digits_count(long digits)
{
	int	i;

	i = 0;
	if (digits == 0)
		return (1);
	else if (digits == -2147483648)
		return (11);
	else if (digits < 0)
	{
		i++;
		digits *= -1;
	}
	while (digits > 0)
	{
		digits /= 10;
		i++;
	}
	return (i);
}
