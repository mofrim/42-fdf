/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:40:42 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 11:39:55 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

static void	print_menu_text(t_myxvar *mx, int x, int y, char *txt);
static void	show_keys(t_myxvar *mx, int *i);
static void	show_mapinfo(t_myxvar *mx, int *i);
static void	print_mapinfo(t_myxvar *mx, const char *txt, int prop, int *i);

void	show_sidebar(t_myxvar *mx)
{
	int		i;

	i = 1;
	show_keys(mx, &i);
	i += 2;
	show_mapinfo(mx, &i);
	i += 2;
	print_menu_text(mx, 15, 20 + (++i) * 15, "-- Current Map Params --");
	i++;
	print_mapinfo(mx, "show_markers: ", mx->show_markers, &i);
	if (mx->show_markers)
		print_mapinfo(mx, "marker_size: ", mx->marker_size, &i);
	print_mapinfo(mx, "mapstyle: ", mx->mapstyle, &i);
	print_mapinfo(mx, "auto_center: ", mx->auto_center_map, &i);
	print_mapinfo(mx, "zfac: ", (int)mx->zfac, &i);
	print_mapinfo(mx, "zoom: ", (int)mx->cur_map->zoom, &i);
	print_mapinfo(mx, "alpha: ", (int)mx->cur_map->alpha, &i);
	print_mapinfo(mx, "beta: ", (int)mx->cur_map->beta, &i);
	print_mapinfo(mx, "gamma: ", (int)mx->cur_map->gamma, &i);
}

static void	print_menu_text(t_myxvar *mx, int x, int y, char *txt)
{
	mlx_string_put(mx->mlx, mx->win, x, y, rgb_to_int("aaaaaa"), txt);
}

static void	show_keys(t_myxvar *mx, int *i)
{
	print_menu_text(mx, 15, 20, "-- Shortcuts --");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "arrows = move map");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, ",/.    = scale height");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "+/-    = zoom in/out");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "q/a    = +/- rot_x");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "w/s    = +/- rot_y");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "e/d    = +/- rot_z");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "i      = draw iso proj");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "1,2,3  = change linestyle");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "m      = toggle markers");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "n/b    = +/- markersize");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "c      = toggle autocenter");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "r      = reset proj");
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "q      = quit program");
}

static void	show_mapinfo(t_myxvar *mx, int *i)
{
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, "-- Map Info --");
	(*i)++;
	print_mapinfo(mx, "map rows: ", mx->orig_map->rows, i);
	print_mapinfo(mx, "map cols: ", mx->orig_map->cols, i);
	print_mapinfo(mx, "winsize_x: ", mx->winsize_x, i);
	print_mapinfo(mx, "winsize_y: ", mx->winsize_y, i);
	print_mapinfo(mx, "xmin: ", (int)mx->xmin, i);
	print_mapinfo(mx, "xmax: ", (int)mx->xmax, i);
	print_mapinfo(mx, "ymin: ", (int)mx->ymin, i);
	print_mapinfo(mx, "ymax: ", (int)mx->ymax, i);
	print_mapinfo(mx, "zmin: ", (int)mx->zmin, i);
	print_mapinfo(mx, "zmax: ", (int)mx->zmax, i);
	print_mapinfo(mx, "zdiff: ", (int)mx->zdiff, i);
}

static void	print_mapinfo(t_myxvar *mx, const char *txt, int prop, int *i)
{
	char	*prop_str;
	char	*msg;

	prop_str = ft_itoa(prop);
	msg = ft_strjoin(txt, prop_str);
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, msg);
	free(msg);
	free(prop_str);
}
