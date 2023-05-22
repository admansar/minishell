NAME = bash

SRC = ft_redirections.c execution.c ft_export.c ft_unset.c  ft_utils.c  main.c ft_change_dir.c ft_pwd.c ft_echo.c ft_here_doc.c

CC = cc

CFLAGS =-Wall -Wextra -Werror -I/goinfre/admansar/homebrew/opt/readline/include -L/goinfre/admansar/homebrew/opt/readline/lib #-g -fsanitize=address

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
