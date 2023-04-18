NAME = bash

SRC = test.c

CC = cc


all : $(NAME)

$(NAME) : $(SRC)
	@make -C libft
	$(CC) $(SRC) libft/libft.a -lreadline -o $(NAME)

clean :
	make -C libft clean

fclean : clean
	make -C libft fclean
	rm -f $(NAME)

re : fclean all
