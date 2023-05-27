NAME = minishell

USER_NAME := $(USER)


SRC = execution.c ft_change_dir.c ft_echo.c ft_export.c ft_here_doc.c ft_pwd.c ft_redirections.c ft_unset.c ft_utils_1.c ft_utils_2.c ft_utils_3.c main.c

CC = cc

CFLAGS =-Wall -Wextra -Werror #-fsanitize=address -g#-I/goinfre/${USER_NAME}/homebrew/opt/readline/include -L/goinfre/${USER_NAME}/homebrew/opt/readline/lib -g -fsanitize=address

all : $(NAME)

$(NAME) : $(SRC) 
	@make -C libft
	$(emo)
	$(CC) $(SRC) ${CFLAGS} libft/libft.a -lreadline -o $(NAME)
	@rm -rf ${NAME}.dSYM

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
