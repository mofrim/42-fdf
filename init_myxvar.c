/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_myxvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:09:21 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/25 23:26:35 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_mlx_win(t_myxvar *mxv);
static void	mxv_set_default_values(t_myxvar *mxv);
static void	mxv_init_map(t_myxvar *mxv, char *mapname);

t_myxvar	*init_myxvar(char *mapname)
{
	t_myxvar	*mxv;

	mxv = malloc(sizeof(t_myxvar));
	nullcheck(mxv, "Malloc of mxv failed");
	init_mlx_win(mxv);
	mxv->winsize_x = WINX;
	mxv->winsize_y = WINY;
	mxv_init_map(mxv, mapname);
	mxv_set_default_values(mxv);
	mxv->colrmap = generate_colrmap(*mxv);
	return (mxv);
}

static void	init_mlx_win(t_myxvar *mxv)
{
	mxv->mlx = mlx_init();
	if (!mxv->mlx)
	{
		ft_printf(" !! mlx_init fail !!\n");
		exit(1);
	}
	mxv->win = mlx_new_window(mxv->mlx, WINX, WINY, "fdf");
	if (!mxv->win)
	{
		ft_printf("!! mlx_new_window fail !!\n");
		exit(1);
	}
}

static void	mxv_init_map(t_myxvar *mxv, char *mapname)
{
	mxv->orig_map = read_map(mapname);
	initial_resize_map(mxv, 0, 0);
	mxv->orig_map->alpha = 0;
	mxv->orig_map->beta = 0;
	mxv->orig_map->gamma = 0;
	mxv->orig_map->y_offset = 0;
	mxv->orig_map->x_offset = 0;
	mxv->orig_map->zoom = 1;
	mxv->xmax = find_map_x_max(*mxv->orig_map);
	mxv->xmin = find_map_x_min(*mxv->orig_map);
	mxv->ymax = find_map_y_max(*mxv->orig_map);
	mxv->ymin = find_map_y_min(*mxv->orig_map);
	mxv->zmax = find_map_z_max(*mxv->orig_map);
	mxv->zmin = find_map_z_min(*mxv->orig_map);
	mxv->zdiff = mxv->zmax - mxv->zmin;
	mxv->cur_map = duplicate_map(mxv->orig_map);
	center_map(mxv);
}

static void	mxv_set_default_values(t_myxvar *mxv)
{
	mxv->auto_center_map = 1;
	mxv->show_markers = 0;
	mxv->marker_size = 4;
}
