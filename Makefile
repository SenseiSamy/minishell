# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:45:28 by cfrancie          #+#    #+#              #
#    Updated: 2023/04/11 22:38:53 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC	= minishell

# **************************************************************************** #

CC		= cc
FLAGS	= -Wall -Wextra -Werror

ifeq ($(MAKECMDGOALS),leaks)
	FLAGS += -ggdb3
endif

# **************************************************************************** #

LDIR	= ./lib/libft/
CDIR	= ./src/
ODIR	= ./bin/
HDIR	= ./inc/

# **************************************************************************** #

LNAME	= libft.a
CNAME	= main.c builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c \
		builtins/export.c builtins/pwd.c builtins/unset.c
		parsing/cmd.c parsing/parsing.c parsing/syntax_checker.c
ONAME	= $(CNAME:.c=.o)
HNAME	= minishell.h

# **************************************************************************** #

CFILES	= $(addprefix $(CDIR), $(CNAME))
OFILES	= $(addprefix $(ODIR), $(ONAME))
HFILES	= $(addprefix $(HDIR), $(HNAME))
LFILES	= $(addprefix $(LDIR), $(LNAME))

# **************************************************************************** #

all: $(EXEC)

$(EXEC): $(OFILES) $(LFILES)
	$(CC) $(FLAGS) -o $(EXEC) $(OFILES) -L$(LDIR) -lft

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