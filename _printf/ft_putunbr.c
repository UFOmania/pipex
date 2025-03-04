/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:54:04 by massrayb          #+#    #+#             */
/*   Updated: 2024/12/12 10:28:29 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(unsigned int unbr)
{
	unsigned int	digits;

	digits = unbr;
	if (unbr > 9)
	{
		ft_putunbr(unbr / 10);
		ft_putchar((unbr % 10) + '0');
	}
	else
		ft_putchar((unbr % 10) + '0');
	return (ft_digits_count(digits));
}
