# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snaji <snaji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:45:28 by cfrancie          #+#    #+#              #
#    Updated: 2023/04/17 23:12:31 by snaji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC	= minishell

# **************************************************************************** #

CC		= cc
FLAGS	= -Wall -Wextra -Werror -g3

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
CNAME	= main.c environment.c environment_utils.c signal.c \
		builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c \
		exec/exec.c exec/builtins.c exec/here_doc.c exec/path.c exec/pipe.c exec/redirections.c exec/utils.c exec/utils2.c
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