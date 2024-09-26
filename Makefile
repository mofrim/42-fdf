# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:55:36 by fmaurer           #+#    #+#              #
#    Updated: 2024/09/26 14:31:55 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

SRCS_IN = ./main.c \
					./read_map.c \
					./get_next_mapline.c \
					./map_functions.c \
					./print_map.c \
					./utils.c \
					./init_myxvar.c \
					./rgb_to_int.c \
					./draw_line.c \
					./matrix.c \
					./draw_map_points.c \
					./general_projection.c \
					./draw_all_the_lines.c \
					./interactive.c \
					./map_trafos.c \
					./draw_map_disks.c \
					./center_map.c \
					./sidebar.c \
					./draw_map_color_elev.c \
					./draw_color_line_elev.c \
					./gen_colormap.c \
					./stereographic_proj.c

SRCS = $(patsubst ./%.c,%.c,$(SRCS_IN))

FDF_HDR	= fdf.h

LIBFT_PATH	= ./libft
LIBFT				= $(LIBFT_PATH)/libft.a

LIB_PATHS = -L./ -L./minilibx-linux/ -L./libft/
LIBS = -lmlx -lXext -lX11 -lm -lft

CC = clang

CFLAGS	=	-Werror -Wall -Wextra
# CFLAGS	=

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT) $(FDF_HDR)
	$(CC) -g $(CFLAGS) $(LIB_PATHS) -o fdf $(SRCS) $(LIBS)
	# ./fdf

$(LIBFT):
	make -C $(LIBFT_PATH) all

win: win.c
	cc -g $(CFLAGS) -o win -L. win.c -lmlx -lXext -lX11

clean: 
	@make -s -C $(LIBFT_PATH) clean


fclean:
	@make -s -C $(LIBFT_PATH) fclean
	@echo "Removing $(NAME) binary..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
