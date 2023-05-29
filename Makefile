NAME = minishell

USER_NAME := $(USER)


SRC = main.c
BUILTIN_PATH = builtins/
UTILS_PATH = utils/
REDIRECTIONS_PATH = redirections/
EXECUTION_PATH = execution/

BUILTIN_SRC = $(addprefix $(BUILTIN_PATH), ft_change_dir.c ft_echo.c ft_export.c ft_pwd.c ft_unset.c)
UTILS_SRC = $(addprefix $(UTILS_PATH), ft_utils_1.c ft_utils_2.c ft_utils_3.c ft_utils_4.c)
REDIRECTIONS_SRC = $(addprefix $(REDIRECTIONS_PATH), ft_redirections.c ft_here_doc.c)
EXECUTION_SRC = $(addprefix $(EXECUTION_PATH), execution.c)

CC = cc

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address #-I/goinfre/${USER_NAME}/homebrew/opt/readline/include -L/goinfre/${USER_NAME}/homebrew/opt/readline/lib -g -fsanitize=address

all : $(NAME)

$(NAME) : $(SRC) $(BUILTIN_SRC) $(UTILS_SRC) $(REDIRECTIONS_SRC) $(EXECUTION_SRC) 
	@make -C libft
	$(emo)
	$(CC) $(SRC) $(BUILTIN_SRC) $(UTILS_SRC) $(REDIRECTIONS_SRC) $(EXECUTION_SRC)  ${CFLAGS} libft/libft.a -lreadline -o $(NAME)

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
