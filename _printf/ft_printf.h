/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:50:26 by massrayb          #+#    #+#             */
/*   Updated: 2024/12/19 17:43:29 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h> 

int	ft_printf(const char *str, ...);
int	ft_opperate(char c, va_list ap);
int	ft_putchar(int c);
int	ft_putstr(char *str);
int	ft_putnbr(int nbr);
int	ft_putunbr(unsigned int nbr);
int	ft_putaddress(unsigned long ptr);
int	ft_digits_count(long nbr);
int	ft_puthex(unsigned int nbr, char *hex_set);
int	ft_strchar(char *str, char c);

#endif 