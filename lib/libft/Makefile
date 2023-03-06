# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:04:31 by cfrancie          #+#    #+#              #
#    Updated: 2023/03/02 22:11:40 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

# **************************************************************************** #

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

# **************************************************************************** #

SRCS	= ./srcs/
OBJS	= ./objs/

# **************************************************************************** #

CFILE	= $(SRCS)ctype.h/ft_isalnum.c \
$(SRCS)ctype.h/ft_isalpha.c \
$(SRCS)ctype.h/ft_isascii.c \
$(SRCS)ctype.h/ft_isblank.c \
$(SRCS)ctype.h/ft_iscntrl.c \
$(SRCS)ctype.h/ft_isdigit.c \
$(SRCS)ctype.h/ft_isgraph.c \
$(SRCS)ctype.h/ft_isprint.c \
$(SRCS)ctype.h/ft_ispunct.c \
$(SRCS)ctype.h/ft_isspace.c \
$(SRCS)ctype.h/ft_isxdigit.c \
$(SRCS)ctype.h/ft_tolower.c \
$(SRCS)ctype.h/ft_toupper.c \
$(SRCS)other/ft_abs.c \
$(SRCS)other/ft_intlen.c \
$(SRCS)other/ft_ldabs.c \
$(SRCS)other/ft_max.c \
$(SRCS)other/ft_min.c \
$(SRCS)other/ft_putchar.c \
$(SRCS)other/ft_putchar_fd.c \
$(SRCS)other/ft_putendl_fd.c \
$(SRCS)other/ft_putnbr_fd.c \
$(SRCS)other/ft_putstr.c \
$(SRCS)other/ft_putstr_fd.c \
$(SRCS)other/ft_search_char.c \
$(SRCS)other/ft_split.c \
$(SRCS)other/ft_striteri.c \
$(SRCS)other/ft_strjoin.c \
$(SRCS)other/ft_strmapi.c \
$(SRCS)other/ft_strtrim.c \
$(SRCS)other/ft_substr.c \
$(SRCS)other/ft_swap.c \
$(SRCS)other/ft_free_split.c \
$(SRCS)stdlib.h/ft_atof.c \
$(SRCS)stdlib.h/ft_atoi.c \
$(SRCS)stdlib.h/ft_atol.c \
$(SRCS)stdlib.h/ft_calloc.c \
$(SRCS)stdlib.h/ft_itoa.c \
$(SRCS)stdlib.h/ft_strdup.c \
$(SRCS)string.h/ft_bzero.c \
$(SRCS)string.h/ft_memchr.c \
$(SRCS)string.h/ft_memcmp.c \
$(SRCS)string.h/ft_memcpy.c \
$(SRCS)string.h/ft_memmove.c \
$(SRCS)string.h/ft_memset.c \
$(SRCS)string.h/ft_strcat.c \
$(SRCS)string.h/ft_strchr.c \
$(SRCS)string.h/ft_strcmp.c \
$(SRCS)string.h/ft_strlcat.c \
$(SRCS)string.h/ft_strlcpy.c \
$(SRCS)string.h/ft_strlen.c \
$(SRCS)string.h/ft_strncat.c \
$(SRCS)string.h/ft_strncmp.c \
$(SRCS)string.h/ft_strncpy.c \
$(SRCS)string.h/ft_strndup.c \
$(SRCS)string.h/ft_strnstr.c \
$(SRCS)string.h/ft_strrchr.c \
$(SRCS)string.h/ft_strstr.c \
$(SRCS)string.h/ft_strnlen.c \

CBFILE	= $(SRCS)other/bonus/ft_lstdelone.c \
$(SRCS)other/bonus/ft_lstlast.c \
$(SRCS)other/bonus/ft_lstnew.c \
$(SRCS)other/bonus/ft_lstadd_back.c \
$(SRCS)other/bonus/ft_lstmap.c \
$(SRCS)other/bonus/ft_lstiter.c \
$(SRCS)other/bonus/ft_lstadd_front.c \
$(SRCS)other/bonus/ft_lstclear.c \
$(SRCS)other/bonus/ft_lstsize.c \

OFILE	= $(CFILE:$(SRCS)%.c=$(OBJS)%.o)

ifeq ($(MAKECMDGOALS), bonus)
	OFILE += $(CBFILE:$(SRCS)%.c=$(OBJS)%.o)
endif

# **************************************************************************** #

COUNTER = 0
TOTAL	= $(words $(CFILE))

# **************************************************************************** #

all: $(NAME)

# **************************************************************************** #

$(NAME): $(OFILE)
	@ar rc $(NAME) $(OFILE)
	@ranlib $(NAME)
	@echo -e "$(GREEN)----------------$(YELLOW)[$(NAME) created]$(GREEN)----------------$(NO_COLOR)"

# **************************************************************************** #

$(OBJS)%.o: $(SRCS)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval COUNTER=$(shell echo $$(($(COUNTER)+1))))
	@echo -e "$(YELLOW)[$(GREEN)$(shell echo $$(($(COUNTER)*100/$(TOTAL))))%$(YELLOW)]$(NO_COLOR) Building C object $(GREEN)$<$(NO_COLOR)"

# **************************************************************************** #

clean:
	@rm -rf $(OBJS)
	@echo -e "$(RED)----------------$(YELLOW)[$(OBJS) deleted]$(RED)----------------$(NO_COLOR)"

# **************************************************************************** #

fclean: clean
	@rm -f $(NAME)
	@echo -e "$(RED)----------------$(YELLOW)[$(NAME) deleted]$(RED)----------------$(NO_COLOR)"

# **************************************************************************** #

bonus:
	@$(MAKE) all

# **************************************************************************** #

re: fclean all

# **************************************************************************** #

.PHONY: all clean fclean bonus re

# **************************************************************************** #

BLACK			=	\033[0;30m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE			=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
LIGHT_GRAY		=	\033[0;37m
DARK_GRAY		=	\033[1;30m
LIGHT_RED		=	\033[1;31m
LIGHT_GREEN		=	\033[1;32m
YELLOW			=	\033[1;33m
LIGHT_BLUE		=	\033[1;34m
LIGHT_PURPLE	=	\033[1;35m
LIGHT_CYAN		=	\033[1;36m
WHITE			=	\033[1;37m
NO_COLOR		=	\033[0m

# **************************************************************************** #