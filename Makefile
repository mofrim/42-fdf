# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 12:55:36 by fmaurer           #+#    #+#              #
#    Updated: 2024/09/09 14:27:39 by fmaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_IN = ./main.c \
					./rgb_to_int.c \
					./draw_line.c

SRCS = $(patsubst ./%.c,%.c,$(SRCS_IN))

LIBS = -lmlx -lXext -lX11 -lm

main:
	cc -g -L./minilibx-linux/ -o fdf $(SRCS) $(LIBS)
	./fdf

win: win.c
	cc -g -o win -L. win.c -lmlx -lXext -lX11

.PHONY: main
