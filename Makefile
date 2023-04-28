# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snaji <snaji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:45:28 by cfrancie          #+#    #+#              #
#    Updated: 2023/04/28 14:13:37 by snaji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC	= minishell

# **************************************************************************** #

CC		= cc
FLAGS	= -Wall -Wextra -Werror -ggdb3

# **************************************************************************** #

LDIR	= ./lib/libft/
CDIR	= ./src/
ODIR	= ./bin/
HDIR	= ./inc/

# **************************************************************************** #

LNAME	=	libft.a
CNAME	=	parsing/parsing_take.c \
			parsing/parsing.c \
			parsing/parsing_utils.c \
			parsing/convert_to_cmd.c \
			parsing/check_syntax.c \
			parsing/utils.c \
			main.c \
			utils.c \
			environment_utils2.c \
			environment_utils.c \
			environment.c \
			signal.c \
			take_parsing.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/env.c \
			builtins/echo.c \
			builtins/cd.c \
			builtins/unset.c \
			builtins/exit.c \
			exec/utils2.c \
			exec/exec.c \
			exec/builtins.c \
			exec/pipe.c \
			exec/here_doc.c \
			exec/here_doc2.c \
			exec/redirections.c \
			exec/path.c \
			exec/utils.c

ONAME	= $(CNAME:.c=.o)
HNAME	= minishell.h exec.h parsing.h

# **************************************************************************** #

CFILES	= $(addprefix $(CDIR), $(CNAME))
OFILES	= $(addprefix $(ODIR), $(ONAME))
HFILES	= $(addprefix $(HDIR), $(HNAME))
LFILES	= $(addprefix $(LDIR), $(LNAME))

# **************************************************************************** #

all: $(EXEC)

$(EXEC): $(OFILES) $(LFILES)
	$(CC) $(FLAGS) -o $(EXEC) $(OFILES) -L$(LDIR) -lft -lreadline

$(ODIR)%.o: $(CDIR)%.c $(HFILES)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -I$(HDIR) -I$(LDIR) -c $< -o $@

$(LFILES):
	$(MAKE) -C $(LDIR)

clean:
	$(MAKE) -C $(LDIR) clean
	rm -rf $(ODIR)

fclean: clean
	$(MAKE) -C $(LDIR) fclean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re