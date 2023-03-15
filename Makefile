# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:45:28 by cfrancie          #+#    #+#              #
#    Updated: 2023/03/15 19:28:14 by cfrancie         ###   ########.fr        #
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
ONAME	= $(CNAME:.c=.o)
HNAME	= minishell.h

# **************************************************************************** #

CFILES	= $(addprefix $(CDIR), $(CNAME))
OFILES	= $(addprefix $(ODIR), $(ONAME))
HFILES	= $(addprefix $(HDIR), $(HNAME))
LFILES	= $(addprefix $(LDIR), $(LNAME))

# **************************************************************************** #

all: $(EXEC)

$(ODIR)%.o: $(CDIR)%.c $(HFILES)
	mkdir -p $(ODIR)
	$(CC) $(FLAGS) -I $(HDIR) -I $(LDIR) -c $< -o $@

$(EXEC): $(OFILES) $(LFILES)
	$(CC) $(FLAGS) -I $(HDIR) -I $(LDIR) -L $(LDIR) -lft $^ -o $@

$(LFILES):
	make -C $(LDIR)

clean:
	rm -rf $(ODIR)
	make -C $(LDIR) clean

fclean: clean
	rm -f $(EXEC)
	make -C $(LDIR) fclean

re: fclean all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)

norme:
	norminette $(CFILES) $(HFILES)
	make -C $(LDIR) norme

.PHONY: all clean fclean re leaks norme