/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:49:33 by massrayb          #+#    #+#             */
/*   Updated: 2024/12/21 10:50:09 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		return_val;

	return_val = 0;
	if (write(1, 0, 0) == -1)
		return (-1);
	va_start(arg, str);
	while (*str != '\0')
	{
		if (*str == '%' && *(str + 1) == '\0')
			break ;
		if (*str == '%')
		{
			str++;
			if (ft_strchar("csdiupxX%", *str))
				return_val += ft_opperate(*str, arg);
		}
		else
			return_val += ft_putchar(*str);
		str++;
	}
	return (return_val);
}
