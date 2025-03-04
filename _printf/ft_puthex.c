/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:50:00 by massrayb          #+#    #+#             */
/*   Updated: 2024/12/19 08:02:29 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int nbr, char *hex_set)
{
	char	address[32];
	int		i;
	int		return_val;

	i = 0;
	if (nbr == 0)
		return (ft_putchar('0'));
	while (nbr > 0)
	{
		address[i] = hex_set[nbr % 16];
		nbr /= 16;
		i++;
	}
	return_val = i;
	while (--i >= 0)
		ft_putchar(address[i]);
	return (return_val);
}
