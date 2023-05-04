# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 19:04:31 by cfrancie          #+#    #+#              #
#    Updated: 2023/04/28 02:45:55 by cfrancie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

# **************************************************************************** #

CC		= cc
FLAGS	= -Wall -Wextra -Werror -g3 -I./

# **************************************************************************** #

CDIR	= ./src/
ODIR	= ./bin/

# **************************************************************************** #

CNAME	= ft_strcat.c \
ft_arraylen.c \
ft_memcmp.c \
ft_isblank.c \
ft_swap.c \
ft_min.c \
ft_strndup.c \
ft_max.c \
ft_putchar.c \
ft_memcpy.c \
ft_calloc.c \
ft_putendl_fd.c \
ft_strnstr.c \
ft_strstr.c \
ft_strncpy.c \
ft_isalpha.c \
ft_strtrim.c \
ft_memmove.c \
ft_isalnum.c \
ft_strcmp.c \
ft_strcpy.c \
ft_isdigit.c \
ft_atof.c \
ft_isxdigit.c \
ft_strncat.c \
ft_ldabs.c \
ft_iscntrl.c \
ft_putstr.c \
ft_abs.c \
ft_isprint.c \
ft_tolower.c \
ft_toupper.c \
ft_search_char.c \
ft_strncmp.c \
ft_strlen.c \
ft_putstr_fd.c \
ft_bzero.c \
ft_atol.c \
ft_strnlen.c \
ft_memset.c \
ft_substr.c \
ft_strmapi.c \
ft_ispunct.c \
ft_strchr.c \
ft_strrev.c \
ft_atoi.c \
ft_isascii.c \
ft_itoa.c \
ft_putchar_fd.c \
ft_strjoin.c \
ft_split.c \
ft_isspace.c \
ft_free_array.c \
ft_strlcat.c \
ft_putnbr_fd.c \
ft_isgraph.c \
ft_memchr.c \
ft_strrchr.c \
ft_striteri.c \
ft_strdup.c \
ft_intlen.c \
ft_strlcpy.c \
ft_printf_c.c \
ft_printf_di.c \
ft_printf_p.c \
ft_printf_s.c \
ft_printf_u.c \
ft_printf_x.c \
ft_vdprintf.c \
ft_printf.c \

BNAME	= ft_lstdelone.c \
ft_lstlast.c \
ft_lstnew.c \
ft_lstadd_back.c \
ft_lstmap.c \
ft_lstiter.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstsize.c \

ONAME	= $(CNAME:.c=.o)
BONAME	= $(BNAME:.c=.o)

# **************************************************************************** #

CFILES	= $(addprefix $(CDIR), $(CNAME))
OFILES	= $(addprefix $(ODIR), $(ONAME))
BFILES	= $(addprefix $(CDIR), $(BNAME))
BOFILES	= $(addprefix $(ODIR), $(BONAME))
HFILES	= $(addprefix ./, libft.h)

ifeq ($(MAKECMDGOALS), bonus)
	OFILES += $(BOFILES)
endif

# **************************************************************************** #

all: $(NAME)

bonus: $(NAME)

$(ODIR): 
	mkdir -p $(ODIR)

$(NAME): $(ODIR) $(OFILES)
	ar rc $(NAME) $(OFILES)
	ranlib $(NAME)

$(ODIR)%.o: $(CDIR)%.c $(HFILES)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norme:
	@norminette $(CFILES) $(CBFILES) $(HFILES)

.PHONY: all bonus clean fclean re norme