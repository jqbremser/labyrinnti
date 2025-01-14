# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 15:41:02 by jbremser          #+#    #+#              #
#    Updated: 2025/01/14 17:36:16 by jbremser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

FLAGS		=	-Wall -Wextra -Werror -g

MLX42		=	MLX42/build/libmlx42.a

MLX42FLAGS	=	-lglfw -L"/usr/local/Cellar/glfw/3.4/lib" -lm

FILES		=	main.c \
				error_handling.c \
				parse_args.c \
				minesweep.c \
				find_functions.c \
				mlx_execution.c \
				utils.c \
				vector_init.c \
				vector_utils.c \
				raycasting.c \
				rendering.c \
				coloring.c \
				movement.c \
				minimap.c

SRCDIR		=	srcs
OBJDIR		=	objs

HEADER		=	header.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SRCS		=	$(addprefix $(SRCDIR)/, $(FILES))

OBJS		=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

ANSI_CYAN 	:= 	\033[0;36m
ANSI_BLUE 	:= 	\033[0;34m
ANSI_RED 	:= 	\033[31m
ANSI_RESET 	:= 	\033[0m

all: 			$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER) 
				@mkdir -p $(OBJDIR)
				@cc $(FLAGS) -o $@ -c $<

$(NAME):		$(OBJS) $(LIBFT)
				@cc $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX42) $(MLX42FLAGS)
				@echo "$(ANSI_CYAN)Compilation Complete: $(NAME) $(ANSI_RESET)"

$(LIBFT):		
				@make -C $(LIBFT_DIR)
				@echo "$(ANSI_CYAN)LIBFT Compiled! $(ANSI_RESET)"

clean:
				@rm -rf $(OBJDIR)
				@make -C $(LIBFT_DIR) clean
				@echo "$(ANSI_RED)Objects and LIB_FT Cleaned$(ANSI_RESET)"

fclean:			clean
				@rm -rf $(NAME)
				@make -C $(LIBFT_DIR) fclean
				@echo "$(ANSI_RED)Executable $(NAME) removed$(ANSI_RESET)"

re:				fclean all

.PHONY: all re clean fclean