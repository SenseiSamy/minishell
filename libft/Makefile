# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:04:31 by cfrancie          #+#    #+#              #
#    Updated: 2023/05/09 01:05:38 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_FT_DPRINTF = ft_dprintf/src/ft_dprintf.c \
                  ft_dprintf/src/ft_putchar_fd.c \
                  ft_dprintf/src/ft_puthex_fd.c \
                  ft_dprintf/src/ft_putnbr_base_fd.c \
                  ft_dprintf/src/ft_putnbr_fd.c \
                  ft_dprintf/src/ft_putptr_fd.c \
                  ft_dprintf/src/ft_putstr_fd.c \
                  ft_dprintf/src/ft_putunbr_fd.c

SRCS_SRC =	src/ft_isascii.c \
			src/ft_ldabs.c \
			src/ft_isgraph.c \
			src/ft_strnlen.c \
			src/ft_ispunct.c \
			src/ft_strncmp.c \
			src/ft_isalpha.c \
			src/ft_strjoin.c \
			src/ft_intlen.c \
			src/ft_memcmp.c \
			src/ft_lstmap.c \
			src/ft_strndup.c \
			src/ft_max.c \
			src/ft_strstr.c \
			src/ft_memchr.c \
			src/ft_strncpy.c \
			src/ft_strcmp.c \
			src/ft_isdigit.c \
			src/ft_strlcpy.c \
			src/ft_lstnew.c \
			src/ft_isspace.c \
			src/ft_strcat.c \
			src/ft_bzero.c \
			src/ft_strrev.c \
			src/ft_atol.c \
			src/ft_strlen.c \
			src/ft_isalnum.c \
			src/ft_strtrim.c \
			src/ft_iscntrl.c \
			src/ft_putendl_fd.c \
			src/ft_swap.c \
			src/ft_memset.c \
			src/ft_isprint.c \
			src/ft_strcpy.c \
			src/ft_strmapi.c \
			src/ft_lstsize.c \
			src/ft_putstr.c \
			src/ft_free_array.c \
			src/ft_striteri.c \
			src/ft_strdup.c \
			src/ft_tolower.c \
			src/ft_strchr.c \
			src/ft_isxdigit.c \
			src/ft_min.c \
			src/ft_strnstr.c \
			src/ft_putnbr_fd.c \
			src/ft_search_char.c \
			src/ft_putstr_fd.c \
			src/ft_strrchr.c \
			src/ft_memcpy.c \
			src/ft_toupper.c \
			src/ft_lstdelone.c \
			src/ft_lstlast.c \
			src/ft_putchar.c \
			src/ft_arraylen.c \
			src/ft_split.c \
			src/ft_isblank.c \
			src/ft_atoi.c \
			src/ft_abs.c \
			src/ft_putchar_fd.c \
			src/ft_calloc.c \
			src/ft_realloc.c \
			src/ft_substr.c \
			src/ft_lstadd_back.c \
			src/ft_strlcat.c \
			src/ft_strtok.c \
			src/ft_memmove.c \
			src/ft_lstadd_front.c \
			src/ft_itoa.c \
			src/ft_lstclear.c \
			src/ft_strnjoin.c \
			src/ft_atof.c \
			src/ft_strncat.c \
			src/ft_lstiter.c

SRCS = $(SRCS_FT_DPRINTF) $(SRCS_SRC)

OBJS = $(SRCS:%.c=./bin/%.o)

INCS = -I./ft_dprintf/include -I.

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^

./bin/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	@rm -rf ./bin

fclean: clean
	@rm $(NAME)

re: fclean all