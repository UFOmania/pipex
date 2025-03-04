/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opperate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:05:05 by massrayb          #+#    #+#             */
/*   Updated: 2024/12/21 04:45:58 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_opperate(char c, va_list ap)
{
	int	return_val;

	return_val = 0;
	if (c == '%')
		return_val += ft_putchar('%');
	else if (c == 'c')
		return_val += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		return_val += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
		return_val += ft_putaddress(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		return_val += ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		return_val += ft_putunbr(va_arg(ap, unsigned int));
	else if (c == 'X')
		return_val += ft_puthex(va_arg(ap, unsigned long), "0123456789ABCDEF");
	else if (c == 'x')
		return_val += ft_puthex(va_arg(ap, unsigned long), "0123456789abcdef");
	else
		return_val = 0;
	return (return_val);
}
