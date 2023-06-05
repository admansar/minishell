NAME = minishell

USER_NAME := $(USER)

SRC = main.c

WILDCARD_PATH = wildcard

BUILTIN_PATH = builtins

UTILS_PATH = utils

REDIRECTIONS_PATH = redirections

EXECUTION_PATH = execution

PARSE_PATH = parsing

BUILTIN_SRC = $(addprefix $(BUILTIN_PATH)/, ft_change_dir.c ft_echo.c ft_export.c ft_pwd.c ft_unset.c ft_exit.c)

PARSE_SRC = $(addprefix $(PARSE_PATH)/, chared_info.c  chared_info_utils1.c chared_info_utils2.c chared_info_utils3.c expand.c  expand_utils1.c  expand_utils2.c  expand_utils3.c  expand_utils4.c  expand_utils5.c  pars_split_join.c pars_utils.c  signals.c  split_and_join.c split_and_join_utils1.c split_and_join_utils2.c utils1.c  utils2.c  utils3.c  utils4.c  utils5.c) 

UTILS_SRC = $(addprefix $(UTILS_PATH)/, env_update_utils.c general_utils_1.c general_utils_2.c\
				here_doc_utils.c redirections_utils_1.c redirections_utils_2.c redirections_utils_3.c\
				utils_export_unset_1.c	utils_export_unset_2.c execution_utils_1.c execution_utils_2.c\
				execution_utils_3.c execution_utils_4.c)

REDIRECTIONS_SRC = $(addprefix $(REDIRECTIONS_PATH)/, ft_redirections.c ft_here_doc.c)

EXECUTION_SRC = $(addprefix $(EXECUTION_PATH)/, execution.c)

WILDCARD_SRC = $(addprefix $(WILDCARD_PATH)/, wildcard_cases.c wildcard_utils1.c the_most_nedded_utils.c wildcard_utils2.c  wildcard.c)

#OBJ_DIR := ./objects

#OBJ = $(OBJ_DIR)/$(SRC:.c=.o) $(OBJ_DIR)/$(BUILTIN_SRC:.c=.o)  $(OBJ_DIR)/$(UTILS_SRC:.c=.o) $(OBJ_DIR)/$(REDIRECTIONS_SRC:.c=.o) $(OBJ_DIR)/$(EXECUTION_SRC:.c=.o) $(OBJ_DIR)/$(WILDCARD_SRC:.c=.o)

SRC_DIR := .

CC = cc

CFLAGS = -Wall -Wextra -Werror -I/goinfre/${USER_NAME}/homebrew/opt/readline/include -L/goinfre/${USER_NAME}/homebrew/opt/readline/lib -g -fsanitize=address

all : $(NAME)

$(NAME) : $(SRC) $(BUILTIN_SRC) $(UTILS_SRC) $(REDIRECTIONS_SRC) $(EXECUTION_SRC) $(WILDCARD_SRC) $(PARSE_SRC)
	@make -C libft
	$(emo)
	$(CC) $(SRC) $(BUILTIN_SRC) $(UTILS_SRC) $(REDIRECTIONS_SRC) $(EXECUTION_SRC) $(WILDCARD_SRC) $(PARSE_SRC) $(CFLAGS) libft/libft.a -lreadline -o $(NAME)

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJ_DIR)/%.o: $(PARSE_PATH)/%.c
#	mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJ_DIR)/%.o: $(WILDCARD_PATH)/%.c
#	mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJ_DIR)/%.o: $(BUILTIN_PATH)/%.c
#	mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJ_DIR)/%.o: $(UTILS_PATH)/%.c
#	mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJ_DIR)/%.o: $(REDIRECTIONS_PATH)/%.c
#	mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJ_DIR)/%.o: $(EXECUTION_PATH)/%.c
#	mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) -c $< -o $@
#
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
