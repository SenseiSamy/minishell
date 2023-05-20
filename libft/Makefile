# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:04:31 by cfrancie          #+#    #+#              #
#    Updated: 2023/05/20 17:39:40 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -fno-builtin -ffreestanding

SDIR = src/
ODIR = bin/
IDIR = include/

CTYPE =		ctype/ft_isspace.c \
			ctype/ft_isxdigit.c \
			ctype/ft_isalnum.c \
			ctype/ft_isdigit.c \
			ctype/ft_tolower.c \
			ctype/ft_toupper.c \
			ctype/ft_isgraph.c \
			ctype/ft_iscntrl.c \
			ctype/ft_isprint.c \
			ctype/ft_isupper.c \
			ctype/ft_islower.c \
			ctype/ft_ispunct.c \
			ctype/ft_isalpha.c

STRING =	string/ft_memset.c \
			string/ft_strncmp.c \
			string/ft_strchr.c \
			string/ft_strlen.c \
			string/ft_strlcpy.c \
			string/ft_strndup.c \
			string/ft_strcpy.c \
			string/ft_strrchr.c \
			string/ft_strncpy.c \
			string/ft_bzero.c \
			string/ft_memcpy.c \
			string/ft_memchr.c \
			string/ft_memcmp.c \
			string/ft_strnstr.c \
			string/ft_strnlen.c \
			string/ft_strlcat.c \
			string/ft_strcmp.c

STDIO =		stdio/ft_dprintf/ft_putstr_fd.c \
			stdio/ft_dprintf/ft_dprintf.c \
			stdio/ft_dprintf/ft_puthex_fd.c \
			stdio/ft_dprintf/ft_putptr_fd.c \
			stdio/ft_dprintf/ft_putchar_fd.c \
			stdio/ft_dprintf/ft_putunbr_fd.c \
			stdio/ft_dprintf/ft_putnbr_base_fd.c \
			stdio/ft_dprintf/ft_putnbr_fd.c

STDLIB =	stdlib/ft_atoll.c \
			stdlib/ft_atol.c \
			stdlib/ft_strdup.c \
			stdlib/ft_calloc.c \
			stdlib/ft_realloc.c \
			stdlib/ft_atoi.c

LIBFT =		libft/ft_len_array.c \
			libft/ft_free_array.c \
			libft/ft_putstr_fd.c \
			libft/ft_split.c \
			libft/ft_strmapi.c \
			libft/ft_striteri.c \
			libft/ft_putchar_fd.c \
			libft/ft_free_array.c \
			libft/ft_strtrim.c \
			libft/ft_strjoin.c \
			libft/ft_substr.c \
			libft/ft_putnbr_fd.c \
			libft/ft_itoa.c \
			libft/ft_putendl_fd.c

CFILE = $(addprefix $(SDIR), $(CTYPE)) \
		$(addprefix $(SDIR), $(STRING)) \
		$(addprefix $(SDIR), $(STDIO)) \
		$(addprefix $(SDIR), $(STDLIB)) \
		$(addprefix $(SDIR), $(LIBFT))

OFILE = $(addprefix $(ODIR), $(CTYPE:.c=.o)) \
		$(addprefix $(ODIR), $(STRING:.c=.o)) \
		$(addprefix $(ODIR), $(STDIO:.c=.o)) \
		$(addprefix $(ODIR), $(STDLIB:.c=.o)) \
		$(addprefix $(ODIR), $(LIBFT:.c=.o))

TOTALFILES = $(words $(CFILE))

all: $(NAME)

$(NAME): $(OFILE)
	@echo -e "\033[32m[OK] \033[0m\033[36mObject files are ready!\033[0m"
	@ar rc $(NAME) $(OFILE)
	@ranlib $(NAME)
	@echo -e "\033[32m[OK] \033[0m\033[36mLibft.a is ready!\033[0m"

$(ODIR)%.o: $(SDIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(IDIR) -o $@ -c $<

clean:
	@rm -rf $(ODIR)
	@rm -f compile_progress
	@echo -e "\033[32m[OK] \033[0m\033[36mObject files are deleted!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo -e "\033[32m[OK] \033[0m\033[36mLibft.a is deleted!\033[0m"

re: fclean all

.PHONY: all clean fclean re