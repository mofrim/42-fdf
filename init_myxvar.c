/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_myxvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:09:21 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 09:50:25 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Helper functions for init mxv. */
static void	init_mlx_win(t_myxvar *mxv);
static void	mxv_set_default_values(t_myxvar *mxv);
static void	mxv_init_map(t_myxvar *mxv, char *mapname);

/* Init. The order of things in this function is crucial! */
t_myxvar	*init_myxvar(char *mapname)
{
	t_myxvar	*mx;

	mx = malloc(sizeof(t_myxvar));
	nullcheck(mx, "Malloc of mx failed");
	init_mlx_win(mx);
	mx->winsize_x = WINX;
	mx->winsize_y = WINY;
	mxv_init_map(mx, mapname);
	mxv_set_default_values(mx);
	mx->colrmap = generate_colrmap(*mx);
	mx->anglst = NULL;
	return (mx);
}

static void	init_mlx_win(t_myxvar *mx)
{
	mx->mlx = mlx_init();
	if (!mx->mlx)
	{
		ft_printf(" !! mlx_init fail !!\n");
		exit(1);
	}
	mx->win = mlx_new_window(mx->mlx, WINX, WINY, "fdf");
	if (!mx->win)
	{
		ft_printf("!! mlx_new_window fail !!\n");
		exit(1);
	}
}

static void	mxv_init_map(t_myxvar *mx, char *mapname)
{
	mx->orig_map = read_map(mapname);
	initial_resize_map(mx);
	mx->orig_map->alpha = 0;
	mx->orig_map->beta = 0;
	mx->orig_map->gamma = 0;
	mx->orig_map->y_offset = 0;
	mx->orig_map->x_offset = 0;
	mx->orig_map->zoom = 1;
	mx->xmax = find_map_x_max(*mx->orig_map);
	mx->xmin = find_map_x_min(*mx->orig_map);
	mx->ymax = find_map_y_max(*mx->orig_map);
	mx->ymin = find_map_y_min(*mx->orig_map);
	mx->zmax = find_map_z_max(*mx->orig_map);
	mx->zmin = find_map_z_min(*mx->orig_map);
	mx->zdiff = mx->zmax - mx->zmin;
	mx->cur_map = duplicate_map(mx->orig_map);
	center_map(mx);
}

static void	mxv_set_default_values(t_myxvar *mxv)
{
	mxv->auto_center_map = 1;
	mxv->show_markers = 0;
	mxv->marker_size = 4;
	mxv->markerstyle = 1;
	mxv->mapstyle = 1;
}
