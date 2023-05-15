# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:45:28 by cfrancie          #+#    #+#              #
#    Updated: 2023/05/15 02:44:32 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBS = -Llibft -lft -lreadline
INCS = -I./inc -I./libft

SRCS_BUILTINS = src/builtins/cd.c \
                src/builtins/echo.c \
                src/builtins/env.c \
                src/builtins/exit.c \
                src/builtins/export.c \
                src/builtins/pwd.c \
                src/builtins/unset.c

SRCS_EXEC = src/exec/builtins.c \
            src/exec/exec.c \
            src/exec/here_doc2.c \
            src/exec/here_doc.c \
            src/exec/path.c \
            src/exec/pipe.c \
            src/exec/redirections.c \
            src/exec/utils2.c \
            src/exec/utils.c

SRCS_PARSING = src/parsing/ambigus_syntax.c \
               src/parsing/conv_cmd.c \
               src/parsing/next_word.c \
               src/parsing/pre_parsing.c \
               src/parsing/syntax_norm.c \
               src/parsing/syntax.c

SRCS = src/environment.c \
       src/environment_utils2.c \
       src/environment_utils.c \
       src/main.c \
       src/signal.c \
       src/utils.c \
       $(SRCS_BUILTINS) \
       $(SRCS_EXEC) \
       $(SRCS_PARSING)

OBJS = $(SRCS:%.c=./bin/%.o)


all: libft $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	$(CC) $(CFLAGS) $(INCS) -o $@ $^ $(LIBS)

./bin/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@rm -rf ./bin
	$(MAKE) -C libft clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re