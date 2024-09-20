/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:40:42 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/20 18:34:42 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	print_menu_text(t_myxvar *mx, int x, int y, char *txt)
{
	mlx_string_put(mx->mlx, mx->win, x, y, rgb_to_int("aa00ff"), txt);
}

void 	draw_menu_back(t_myxvar mxv)
{
	int	j;
	int	k;
	t_line	border;

	j = 4;
	while (++j < 250)
	{
		k = 4;
		while (++k < 180)
		{
			mlx_pixel_put(mxv.mlx, mxv.win, j, k, rgb_to_int("bbbbbb"));
		}
	}
	border.x0 = 5;
	border.y0 = 180;
	border.x1 = 250;
	border.y1 = 180;
	draw_thick_line(border, "00bb00", mxv);
	border.x0 = 250;
	border.y0 = 5;
	border.x1 = 250;
	border.y1 = 180;
	draw_thick_line(border, "00bb00", mxv);
	border.x0 = 5;
	border.y0 = 5;
	border.x1 = 250;
	border.y1 = 5;
	draw_thick_line(border, "00bb00", mxv);
	border.x0 = 5;
	border.y0 = 5;
	border.x1 = 5;
	border.y1 = 180;
	draw_thick_line(border, "00bb00", mxv);
}

void	show_menu(t_myxvar *mxv)
{
	draw_menu_back(*mxv);
	print_menu_text(mxv, 15, 20,	"Menu");
	print_menu_text(mxv, 15, 45,	"m      = toggle menu");
	print_menu_text(mxv, 15, 60,	"arrows = move map");
	print_menu_text(mxv, 15, 75,	",/.    = scale height");
	print_menu_text(mxv, 15, 90,	"+/-    = zoom in/out");
	print_menu_text(mxv, 15, 105,	"x/s    = +/- rot_x");
	print_menu_text(mxv, 15, 120,	"y/a    = +/- rot_y");
	print_menu_text(mxv, 15, 135,	"z/h    = +/- rot_z");
	print_menu_text(mxv, 15, 150,	"c      = center map");
	print_menu_text(mxv, 15, 165,	"q      = quit program");
}

