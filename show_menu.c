/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:40:42 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/21 16:00:21 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	print_menu_text(t_myxvar *mx, int x, int y, char *txt)
{
	mlx_string_put(mx->mlx, mx->win, x, y, rgb_to_int("aa00ff"), txt);
}

void	draw_menu_back(t_myxvar mxv, int menu_width, int menu_height)
{
	int	j;
	int	k;

	j = 4;
	while (++j < menu_width)
	{
		k = 4;
		while (++k < menu_height)
			mlx_pixel_put(mxv.mlx, mxv.win, j, k, rgb_to_int("bbbbbb"));
	}
}

void	draw_menu_border(t_myxvar mxv, int menu_width, int menu_height)
{
	t_line	border;

	border.x0 = 5;
	border.y0 = menu_height;
	border.x1 = menu_width;
	border.y1 = menu_height;
	draw_thick_line(border, "00bb00", mxv);
	border.x0 = menu_width;
	border.y0 = 5;
	border.x1 = menu_width;
	border.y1 = menu_height;
	draw_thick_line(border, "00bb00", mxv);
	border.x0 = 5;
	border.y0 = 5;
	border.x1 = menu_width;
	border.y1 = 5;
	draw_thick_line(border, "00bb00", mxv);
	border.x0 = 5;
	border.y0 = 5;
	border.x1 = 5;
	border.y1 = menu_height;
	draw_thick_line(border, "00bb00", mxv);
}

void	draw_menu_deco(t_myxvar mxv, int menu_width, int menu_height)
{
	draw_menu_back(mxv, menu_width, menu_height);
	draw_menu_border(mxv, menu_width, menu_height);
}

void	show_menu(t_myxvar *mxv)
{
	draw_menu_deco(*mxv, 250, 220);
	print_menu_text(mxv, 15, 20, "Menu");
	print_menu_text(mxv, 15, 45, "m      = toggle menu");
	print_menu_text(mxv, 15, 60, "arrows = move map");
	print_menu_text(mxv, 15, 75, ",/.    = scale height");
	print_menu_text(mxv, 15, 90, "+/-    = zoom in/out");
	print_menu_text(mxv, 15, 105, "x/s    = +/- rot_x");
	print_menu_text(mxv, 15, 120, "y/a    = +/- rot_y");
	print_menu_text(mxv, 15, 135, "z/h    = +/- rot_z");
	print_menu_text(mxv, 15, 150, "i      = draw iso proj");
	print_menu_text(mxv, 15, 165, "r      = reset proj");
	print_menu_text(mxv, 15, 180, "c      = center map");
	print_menu_text(mxv, 15, 195, "q      = quit program");
}
