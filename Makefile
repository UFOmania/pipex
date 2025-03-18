CFLAGS = -Wall -Wextra -Werror

SRC =	pipex.c\
		parse.c\
		utils.c\
		error_handler.c\
		env_handler.c\
		config_pipe.c\
		child.c

OBJ = $(SRC:.c=.o)

all: libft printf $(OBJ)
	cc $(CFLAGS) $(OBJ) _libft/libft.a _printf/libftprintf.a -o pipex

libft:
	make -C _libft/

printf:
	make -C _printf/

%.o: %.c pipex.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C _libft/ clean
	make -C _printf/ clean

fclean: clean
	rm -f pipex

re: fclean all