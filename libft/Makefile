# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 10:55:21 by jbremser          #+#    #+#              #
#    Updated: 2024/12/10 14:01:08 by jbremser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFILES =	ft_memset.c \
		 	ft_bzero.c \
		 	ft_calloc.c \
		 	ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_itoa.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_putchar_fd.c \
			ft_putnbr_fd.c \
			ft_substr.c \
			ft_strtrim.c \
			ft_split.c \
			ft_strjoin.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_printf.c \
			print_ch.c \
			print_str.c \
			cast_hex.c \
			cast_dec.c \
			printp.c \
			get_next_line.c 	
		 
ANSI_BLUE := \033[0;34m
ANSI_RED :=	\033[31m
ANSI_RESET := \033[0m		 	 

OFILES = $(CFILES:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME) 

$(NAME): $(OFILES) 
	@ar -rcs $(NAME) $(OFILES)
	@echo "$(ANSI_BLUE)LIBFT Compilation Complete$(ANSI_RESET)"

%.o: %.c
	@cc $(FLAGS) -o $@ -c $<

clean:
	@rm -f $(OFILES)
	@echo "$(ANSI_RED)LIBFT cleaned$(ANSI_RESET)" 

fclean: clean
	@rm -f $(NAME)
	@echo "$(ANSI_RED)$(NAME) removed$(ANSI_RESET)"

re: fclean $(NAME)

.PHONY : all clean fclean re 
