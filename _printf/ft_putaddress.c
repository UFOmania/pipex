/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:52:00 by massrayb          #+#    #+#             */
/*   Updated: 2024/12/19 17:55:29 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putaddress(unsigned long ptr)
{
	char	*hex_set;
	char	address[32];
	int		i;
	int		return_val;

	i = 0;
	hex_set = "0123456789abcdef";
	if (ptr == 0)
		return (ft_putstr("0x0"));
	else
		ft_putstr("0x");
	while (ptr > 0)
	{
		address[i] = hex_set[ptr % 16];
		ptr /= 16;
		i++;
	}
	return_val = i + 2;
	while (--i >= 0)
		ft_putchar(address[i]);
	return (return_val);
}
