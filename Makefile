# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:55:36 by fmaurer           #+#    #+#              #
#    Updated: 2024/09/30 18:54:31 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

SRCS_IN = ./main.c \
					./init_myxvar.c \
					./read_map.c \
					./get_next_mapline.c \
					./map_functions.c \
					./sidebar.c \
					./print_map.c \
					./kbd_input_handler.c \
					./kbd_style.c \
					./kbd_utility.c \
					./kbd_trafo.c \
					./draw_map.c \
					./gen_colormap.c \
					./draw_map_disks.c \
					./draw_line_colr_elev.c \
					./draw_line_nocolr.c \
					./rotate_map.c \
					./map_trafos.c \
					./center_map_findx.c \
					./find_yz_minmax.c\
					./rot_xyz.c \
					./utils.c \
					./rgb_to_int.c \
					./matrix.c \
					./close_btn_handler.c \
					./print_float.c \
					./anglst.c

SRCS = $(patsubst ./%.c,%.c,$(SRCS_IN))

OBJS_DIR = obj
OBJS	= $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS)) 

LIBFT_PATH	= ./libft
LIBFT				= $(LIBFT_PATH)/libft.a

LIBMLX_PATH = ./minilibx-linux
LIBMLX = ./minilibx-linux/libmlx.a

LIB_PATHS = -L$(LIBMLX_PATH) -L$(LIBFT_PATH)
LIBS = -lmlx -lXext -lX11 -lm -lft

FDF_HDR	= fdf.h
INC = -I$(LIBMLX_PATH) -I$(LIBFT_PATH)

CC = cc
CFLAGS	=	-Werror -Wall -Wextra

all: $(NAME)

$(OBJS_DIR)/%.o : %.c $(FDF_HDR)
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(INC) $(LIB_PATHS) -o fdf $(OBJS) $(LIBS)

$(LIBFT):
	make -C $(LIBFT_PATH) all

$(LIBMLX):
	NIX11=$NIX11 make -C ./minilibx-linux/

bonus: $(NAME)

mlx: $(LIBMLX)

debug: $(SRCS) $(LIBFT) $(LIBMLX) $(FDF_HDR)
	$(CC) -g $(CFLAGS) $(INC) $(LIB_PATHS) -o fdf $(SRCS) $(LIBS)

setup:
	@echo "Setting things up..."
	@echo
	@wget https://cdn.intra.42.fr/document/document/26195/maps.zip
	@wget https://cdn.intra.42.fr/document/document/26198/minilibx-linux.tgz
	@tar xzf ./minilibx-linux.tgz
	@unzip ./maps.zip
	@rm -rf ./__MACOSX

clean: 
	@echo "Removing libft objs."
	@make -s -C $(LIBFT_PATH) clean
	@echo "Removing libmlx objs."
	@make -s -C $(LIBMLX_PATH) clean
	@echo "Removing fdf objs."
	@rm -rf $(OBJS_DIR)

fclean:
	@echo "fcleaning libft."
	@make -s -C $(LIBFT_PATH) fclean
	@echo "fcleaning libmlx."
	@make -s -C $(LIBMLX_PATH) clean
	@echo "Removing fdf objs."
	@rm -rf $(OBJS_DIR)
	@echo "Removing $(NAME) binary."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx debug bonus setup
