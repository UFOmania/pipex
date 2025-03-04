# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: massrayb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 19:29:24 by massrayb          #+#    #+#              #
#    Updated: 2024/12/21 10:15:41 by massrayb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = 	cc
FLAGS =	-Wall -Werror -Wextra
AR = 	ar r

SRC = 	ft_printf.c\
		ft_putchar.c\
		ft_putstr.c\
		ft_putnbr.c\
		ft_putnbr.c\
		ft_putunbr.c\
		ft_putaddress.c\
		ft_opperate.c\
		ft_puthex.c\
		ft_utils.c

OBJ		= $(SRC:.c=.o)

NAME	= libftprintf.a

all:	$(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $(OBJ)

%.o:	%.c ft_printf.h
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:		fclean all
