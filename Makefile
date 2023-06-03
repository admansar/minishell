NAME = minishell

USER_NAME := $(USER)

SRC = main.c

WILDCARD_PATH = wildcard

BUILTIN_PATH = builtins

UTILS_PATH = utils

REDIRECTIONS_PATH = redirections

EXECUTION_PATH = execution

PARSE_PATH = parsing/

BUILTIN_SRC = $(addprefix $(BUILTIN_PATH)/, ft_change_dir.c ft_echo.c ft_export.c ft_pwd.c ft_unset.c)

UTILS_SRC = $(addprefix $(UTILS_PATH)/, ft_utils_1.c ft_utils_2.c ft_utils_3.c ft_utils_4.c)

REDIRECTIONS_SRC = $(addprefix $(REDIRECTIONS_PATH)/, ft_redirections.c ft_here_doc.c)

EXECUTION_SRC = $(addprefix $(EXECUTION_PATH)/, execution.c)

WILDCARD_SRC = $(addprefix $(WILDCARD_PATH)/, wildcard_cases.c wildcard_utils1.c  the_most_nedded_utils.c wildcard_utils2.c  wildcard.c)

OBJ_DIR := ./objects

OBJ = $(OBJ_DIR)/$(SRC:.c=.o) $(OBJ_DIR)/$(BUILTIN_SRC:.c=.o)  $(OBJ_DIR)/$(UTILS_SRC:.c=.o) $(OBJ_DIR)/$(REDIRECTIONS_SRC:.c=.o) $(OBJ_DIR)/$(EXECUTION_SRC:.c=.o) $(OBJ_DIR)/$(WILDCARD_SRC:.c=.o)

SRC_DIR := .

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address #-I/goinfre/${USER_NAME}/homebrew/opt/readline/include -L/goinfre/${USER_NAME}/homebrew/opt/readline/lib -g -fsanitize=address

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft
	$(emo)
	$(CC) $(OBJ) $(CFLAGS) libft/libft.a -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(WILDCARD_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BUILTIN_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(REDIRECTIONS_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXECUTION_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make -C libft clean
	rm -rf objects
	@rm -f */*.o *.o

fclean : clean
	@rm -rf ${NAME}.dSYM
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
