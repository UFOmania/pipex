CFLAGS =  -Wall -Wextra -Wall
NAME=pipex

LIBFT = _libft/libft.a
PRINTF = _printf/libftprintf.a

SRC =	src/pipex.c\
		src/parser.c\
		src/execute.c\
		src/clean.c\

OBJ = $(SRC:.c=.o)


all: libft printf $(NAME)

libft:
	make -C _libft/

printf:
	make -C _printf/

$(NAME): $(OBJ) 
	cc $(CFLAGS) $(LIBFT) $(PRINTF) $(OBJ) -o $@

src/%.o: %.c include/pipex.h
	cc $(CFLAGS) -c $<

clean:
	make fclean -C _libft
	make fclean -C _printf
	rm -rf $(OBJ)

re: fclean all

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(LIBFT)

