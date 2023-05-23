# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:45:28 by cfrancie          #+#    #+#              #
#    Updated: 2023/05/23 18:52:45 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb3
LIBS = -Llibft -lft -lreadline
INCS = -I./include -I./libft/include


SRCS_BUILTINS = src/builtins/cd.c \
                src/builtins/echo.c \
                src/builtins/env.c \
                src/builtins/exit.c \
                src/builtins/export.c \
                src/builtins/pwd.c \
                src/builtins/unset.c

SRCS_EXEC = 	src/exec/builtins.c \
				src/exec/exec.c \
				src/exec/here_doc2.c \
				src/exec/here_doc.c \
				src/exec/path.c \
				src/exec/pipe.c \
				src/exec/redirections.c \
				src/exec/utils2.c \
				src/exec/utils.c

SRCS_PARSING =	src/parsing/ambigus_syntax.c \
				src/parsing/conv_cmd.c \
				src/parsing/next_word.c \
				src/parsing/pre_parsing.c \
				src/parsing/syntax_norm.c \
				src/parsing/syntax.c \
				src/parsing/size_pre_parsing.c

SRCS = 			src/environment.c \
				src/environment_utils2.c \
				src/environment_utils.c \
				src/main.c \
				src/signal.c \
				src/utils.c \
				$(SRCS_BUILTINS) \
				$(SRCS_EXEC) \
				$(SRCS_PARSING)

OBJS = $(SRCS:%.c=./bin/%.o)

TOTAL_SRCS := $(words $(SRCS))
CURRENT_SRC := 0
PERCENTAGE := 0

# Couleurs du texte
DEFAULT = "\033[0m"
BOLD = "\033[1m"
UNDERLINE = "\033[4m"
BLACK = "\033[30m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
WHITE = "\033[37m"

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	$(CC) $(CFLAGS) $(INCS) -o $@ $^ $(LIBS)

# 	@echo $(BOLD)$(UNDERLINE)$(BLUE)"Compiling "$(NAME)"... "$(DEFAULT)$(PERCENTAGE)$(BOLD)$(UNDERLINE)$(BLUE)"%"$(DEFAULT)$(BOLD)$(UNDERLINE)$(BLUE)" ["$(DEFAULT)$(GREEN)$(CURRENT_SRC)$(DEFAULT)$(BOLD)$(UNDERLINE)$(BLUE)"/"$(DEFAULT)$(GREEN)$(TOTAL_SRCS)$(DEFAULT)$(BOLD)$(UNDERLINE)$(BLUE)"]"$(DEFAULT)$(BOLD)$(UNDERLINE)$(BLUE)" "$(DEFAULT)$(BOLD)$(UNDERLINE)$(BLUE)"["$<"]"$(DEFAULT)

./bin/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@$(eval CURRENT_SRC := $(shell echo $$(($(CURRENT_SRC) + 1))))
	@$(eval PERCENTAGE := $(shell echo $$(($(CURRENT_SRC) * 100 / $(TOTAL_SRCS)))))
	@echo [$(GREEN)$(PERCENTAGE)%$(DEFAULT): $(GREEN)$(CURRENT_SRC)$(DEFAULT)/$(GREEN)$(TOTAL_SRCS)$(DEFAULT)] [$(BOLD)$(UNDERLINE)$(BLUE)$<$(DEFAULT)]

clean:
	@rm -rf ./bin
	$(MAKE) -C libft clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re