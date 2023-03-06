# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:45:28 by cfrancie          #+#    #+#              #
#    Updated: 2023/03/06 16:41:55 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC	= minishell

# **************************************************************************** #

CC		= cc
FLAGS	= -Wall -Wextra -Werror

ifeq ($(MAKECMDGOALS),debug)
	FLAGS += -ggdb3
endif

# **************************************************************************** #

LDIR	= ./lib/libft
CDIR	= ./src/
ODIR	= ./bin/
HDIR	= ./inc/

# **************************************************************************** #

LNAME	= libft.a
CNAME	= main.c
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
	$(CC) $(FLAGS) -o $@ -c $< -I$(HDIR)

$(LFILES):
	make -C $(LDIR)

clean:
	rm -f $(OFILES)
	make clean -C $(LDIR)

fclean: clean
	rm -f $(EXEC)
	make fclean -C $(LDIR)

re: fclean all

debug: re

leaks: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

norme:
	norminette $(CFILES) $(HFILES)

.PHONY: all clean fclean re debug leaks norme
