# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:55:36 by fmaurer           #+#    #+#              #
#    Updated: 2024/09/19 11:26:37 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

SRCS_IN = ./main.c \
					./rgb_to_int.c \
					./draw_line.c \
					./read_map.c \
					./utils.c \
					./matrix.c \
					./draw_map_points.c \
					./isometric_projection.c \
					./draw_all_the_lines.c \
					./line_lst_funcs.c \
					./interactive.c \
					./map_trafos.c \
					./map_functions.c \
					./pixelcloud_funcs.c

SRCS = $(patsubst ./%.c,%.c,$(SRCS_IN))

FDF_HDR	= fdf.h

LIBFT_PATH	= ./libft
LIBFT				= $(LIBFT_PATH)/libft.a

LIB_PATHS = -L./ -L./minilibx-linux/ -L./libft/
LIBS = -lmlx -lXext -lX11 -lm -lft

# CFLAGS	=	-Werror -Wall -Wextra
CFLAGS	=

$(NAME): $(SRCS) $(LIBFT) $(FDF_HDR)
	cc -g $(CFLAGS) $(LIB_PATHS) -o fdf $(SRCS) $(LIBS)
	# ./fdf

$(LIBFT):
	make -C $(LIBFT_PATH) all

win: win.c
	cc -g $(CFLAGS) -o win -L. win.c -lmlx -lXext -lX11

clean: fclean

fclean:
	@make -s -C $(LIBFT_PATH) fclean
	@echo "Removing $(NAME) binary..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
