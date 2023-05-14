NAME = bash

SRC = execution.c ft_export.c ft_unset.c  ft_utils.c  main.c

CC = cc

CFLAGS =-Wall -Wextra -Werror -g -fsanitize=address

all : $(NAME)

$(NAME) : $(SRC) 
	@make -C libft
	$(emo)
	$(CC) $(SRC) ${CFLAGS} libft/libft.a -lreadline -o $(NAME)

clean :
	make -C libft clean

fclean : clean
	rm -rf ${NAME}.dSYM
	make -C libft fclean
	rm -f $(NAME)

re : fclean all

define emo
@echo "\033[0;91m" 
@echo "\t█████████████████████████████████████████████████████"
@echo "\t█▄─▀█▀─▄█▄─▄█▄─▀█▄─▄█▄─▄█─▄▄▄▄█─█─█▄─▄▄─█▄─▄███▄─▄███"
@echo "\t██─█▄█─███─███─█▄▀─███─██▄▄▄▄─█─▄─██─▄█▀██─██▀██─██▀█"
@echo "\t█▄▄▄█▄▄▄█▄▄▄█▄▄▄██▄▄█▄▄▄█▄▄▄▄▄█▄█▄█▄▄▄▄▄█▄▄▄▄▄█▄▄▄▄▄█"
@echo "\033[0m"
endef
