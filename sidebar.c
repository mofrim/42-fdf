/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:40:42 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/25 20:35:55 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

void	print_menu_text(t_myxvar *mx, int x, int y, char *txt)
{
	mlx_string_put(mx->mlx, mx->win, x, y, rgb_to_int("aaaaaa"), txt);
}

// TODO deprecate.
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

// TODO deprecate.
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

// TODO deprecate.
void	draw_menu_deco(t_myxvar mxv, int menu_width, int menu_height)
{
	draw_menu_back(mxv, menu_width, menu_height);
	draw_menu_border(mxv, menu_width, menu_height);
}

// TODO rename to show_info, split into seperate funcs for info and shortcuts.
void	show_sidebar(t_myxvar *mxv)
{
	int	i;
	char	*txt;
	char	*prop;

	i = 1;
	print_menu_text(mxv, 15, 20, "-- Shortcuts --");
	print_menu_text(mxv, 15, 20 + (++i)*15, "arrows = move map");
	print_menu_text(mxv, 15, 20 + (++i)*15, ",/.    = scale height");
	print_menu_text(mxv, 15, 20 + (++i)*15, "+/-    = zoom in/out");
	print_menu_text(mxv, 15, 20 + (++i)*15, "q/a    = +/- rot_x");
	print_menu_text(mxv, 15, 20 + (++i)*15, "w/s    = +/- rot_y");
	print_menu_text(mxv, 15, 20 + (++i)*15, "e/d    = +/- rot_z");
	print_menu_text(mxv, 15, 20 + (++i)*15, "i      = draw iso proj");
	print_menu_text(mxv, 15, 20 + (++i)*15, "r      = reset proj");
	print_menu_text(mxv, 15, 20 + (++i)*15, "c      = toggle autocenter");
	print_menu_text(mxv, 15, 20 + (++i)*15, "m      = toggle markers");
	print_menu_text(mxv, 15, 20 + (++i)*15, "q      = quit program");
	print_menu_text(mxv, 15, 20 + (++i)*15, "q      = quit program");
	i += 2;
	print_menu_text(mxv, 15, 20 + (++i)*15, "-- Map Info --");
	i++;
	prop = ft_itoa(mxv->orig_map->rows);
	txt = ft_strjoin("map rows: ", prop);
	print_menu_text(mxv, 15, 20 + (++i)*15, txt);
	free(txt);
	free(prop);
	prop = ft_itoa(mxv->orig_map->cols);
	txt = ft_strjoin("map cols: ", prop);
	print_menu_text(mxv, 15, 20 + (++i)*15, txt);
	free(txt);
	free(prop);
	prop = ft_itoa(mxv->auto_center_map);
	txt = ft_strjoin("auto_center: ", prop);
	print_menu_text(mxv, 15, 20 + (++i)*15, txt);
	free(txt);
	free(prop);
	prop = ft_itoa((int)mxv->zfac);
	txt = ft_strjoin("zfac: ", prop);
	print_menu_text(mxv, 15, 20 + (++i)*15, txt);
	free(txt);
	free(prop);
	prop = ft_itoa((int)mxv->xyfac);
	txt = ft_strjoin("xyfac: ", prop);
	print_menu_text(mxv, 15, 20 + (++i)*15, txt);
	free(txt);
	free(prop);
	prop = ft_itoa((int)mxv->zmax);
	txt = ft_strjoin("zmax: ", prop);
	print_menu_text(mxv, 15, 20 + (++i)*15, txt);
	free(txt);
	free(prop);
	prop = ft_itoa((int)mxv->zdiff);
	txt = ft_strjoin("zdiff: ", prop);
	print_menu_text(mxv, 15, 20 + (++i)*15, txt);
	free(txt);
	free(prop);
}
