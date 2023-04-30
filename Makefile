NAME = bash

SRC = test.c

CC = cc

CFLAGS = -g -fsanitize=address


all : $(NAME)

$(NAME) : $(SRC)
	@make -C libft
	$(CC) $(SRC) $(CFLAGS) libft/libft.a -lreadline -o $(NAME)

clean :
	make -C libft clean

fclean : clean
	make -C libft fclean
	rm -f $(NAME)

re : fclean all
