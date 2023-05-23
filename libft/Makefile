# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:04:31 by cfrancie          #+#    #+#              #
#    Updated: 2023/05/23 19:08:42 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -fno-builtin -ffreestanding

SDIR = src/
ODIR = bin/
IDIR = include/

BONUS =		bonus/ft_lstdelone.c \
			bonus/ft_lstadd_front.c \
			bonus/ft_lstclear.c \
			bonus/ft_lstadd_back.c \
			bonus/ft_lstnew.c \
			bonus/ft_lstsize.c \
			bonus/ft_lstiter.c \
			bonus/ft_lstmap.c \
			bonus/ft_lstlast.c

CTYPE =		ctype/ft_isalpha.c \
			ctype/ft_isalnum.c \
			ctype/ft_isdigit.c \
			ctype/ft_isxdigit.c \
			ctype/ft_iscntrl.c \
			ctype/ft_isprint.c \
			ctype/ft_tolower.c \
			ctype/ft_toupper.c \
			ctype/ft_ispunct.c \
			ctype/ft_isspace.c \
			ctype/ft_islower.c \
			ctype/ft_isupper.c \
			ctype/ft_isgraph.c \

STRING =	string/ft_memcmp.c \
			string/ft_strndup.c \
			string/ft_memcpy.c \
			string/ft_strnstr.c \
			string/ft_strncpy.c \
			string/ft_strcmp.c \
			string/ft_strcpy.c \
			string/ft_strncmp.c \
			string/ft_strlen.c \
			string/ft_bzero.c \
			string/ft_strnlen.c \
			string/ft_memset.c \
			string/ft_strchr.c \
			string/ft_strlcat.c \
			string/ft_memchr.c \
			string/ft_strrchr.c \
			string/ft_strlcpy.c \

STDIO =		stdio/ft_dprintf/ft_dprintf.c \
			stdio/ft_dprintf/ft_puthex_fd.c \
			stdio/ft_dprintf/ft_putptr_fd.c \
			stdio/ft_dprintf/ft_putunbr_fd.c \
			stdio/ft_dprintf/ft_putstr_fd.c \
			stdio/ft_dprintf/ft_putnbr_base_fd.c \
			stdio/ft_dprintf/ft_putchar_fd.c \
			stdio/ft_dprintf/ft_putnbr_fd.c \

STDLIB =	stdlib/ft_calloc.c \
			stdlib/ft_realloc.c \
			stdlib/ft_atol.c \
			stdlib/ft_atoi.c \
			stdlib/ft_atoll.c \
			stdlib/ft_strdup.c \

LIBFT =		libft/ft_putendl_fd.c \
			libft/ft_strtrim.c \
			libft/ft_putstr_fd.c \
			libft/ft_substr.c \
			libft/ft_strmapi.c \
			libft/ft_itoa.c \
			libft/ft_putchar_fd.c \
			libft/ft_strjoin.c \
			libft/ft_split.c \
			libft/ft_len_array.c \
			libft/ft_free_array.c \
			libft/ft_putnbr_fd.c \
			libft/ft_striteri.c \

CFILE = $(addprefix $(SDIR), $(BONUS)) \
		$(addprefix $(SDIR), $(CTYPE)) \
		$(addprefix $(SDIR), $(STRING)) \
		$(addprefix $(SDIR), $(STDIO)) \
		$(addprefix $(SDIR), $(STDLIB)) \
		$(addprefix $(SDIR), $(LIBFT))

OFILE = $(addprefix $(ODIR), $(BONUS:.c=.o)) \
		$(addprefix $(ODIR), $(CTYPE:.c=.o)) \
		$(addprefix $(ODIR), $(STRING:.c=.o)) \
		$(addprefix $(ODIR), $(STDIO:.c=.o)) \
		$(addprefix $(ODIR), $(STDLIB:.c=.o)) \
		$(addprefix $(ODIR), $(LIBFT:.c=.o))


TOTAL_SRCS := $(words $(CFILE))
CURRENT_SRC := 0
PERCENTAGE := 0

DEFAULT = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

all: $(NAME)

$(NAME): $(OFILE)
	@ar rc $(NAME) $(OFILE)
	@ranlib $(NAME)
	@echo "[$(GREEN)OK$(DEFAULT)] $(BOLD)$(UNDERLINE)$(BLUE)$(NAME)$(DEFAULT) is created!"

$(ODIR)%.o: $(SDIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(IDIR) -o $@ -c $<
	@$(eval CURRENT_SRC := $(shell echo $$(($(CURRENT_SRC) + 1))))
	@$(eval PERCENTAGE := $(shell echo $$(($(CURRENT_SRC) * 100 / $(TOTAL_SRCS)))))
	@echo "[$(GREEN)$(PERCENTAGE)%$(DEFAULT): $(GREEN)$(CURRENT_SRC)$(DEFAULT)/$(GREEN)$(TOTAL_SRCS)$(DEFAULT)] [$(BOLD)$(UNDERLINE)$(BLUE)$<$(DEFAULT)]"

clean:
	@rm -rf $(ODIR)
	@echo "[$(RED)OK$(DEFAULT)] $(BOLD)$(UNDERLINE)$(BLUE)$(ODIR) is deleted!$(DEFAULT)"

fclean: clean
	@rm -rf $(NAME)
	@echo "[$(RED)OK$(DEFAULT)] $(BOLD)$(UNDERLINE)$(BLUE)$(NAME) is deleted!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re