/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_trafos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:44:31 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 23:33:34 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rot_map_x(t_map *map, double angl)
{
	double rot_x[3][3];

	map->alpha += angl;
	rot_x[0][0] = 1;
	rot_x[0][1] = 0;
	rot_x[0][2] = 0;
	rot_x[1][0] = 0;
	rot_x[1][1] = cos(map->alpha);
	rot_x[1][2] = sin(map->alpha);
	rot_x[2][0] = 0;
	rot_x[2][1] = -sin(map->alpha);
	rot_x[2][2] = cos(map->alpha);
	mult_mat_map(rot_x, map);
}

void	rot_map_y(t_map *map, double angl)
{
	double rot_y[3][3];

	map->beta += angl;
	rot_y[0][0] = cos(map->beta);
	rot_y[0][1] = 0;
	rot_y[0][2] = sin(map->beta);
	rot_y[1][0] = 0;
	rot_y[1][1] = 1;
	rot_y[1][2] = 0;
	rot_y[2][0] = -sin(map->beta);
	rot_y[2][1] = 0;
	rot_y[2][2] = cos(map->beta);
	mult_mat_map(rot_y, map);
}

void	rot_map_z(t_map *map, double angl)
{
	double rot_z[3][3];

	map->gamma += angl;
	rot_z[0][0] = cos(map->gamma);
	rot_z[0][1] = sin(map->gamma);
	rot_z[0][2] = 0;
	rot_z[1][0] = -sin(map->gamma);
	rot_z[1][1] = cos(map->gamma);
	rot_z[1][2] = 0;
	rot_z[2][0] = 0;
	rot_z[2][1] = 0;
	rot_z[2][2] = 1;
	mult_mat_map(rot_z, map);
}

void	proj_map_to_xy(t_map *map)
{
	double proj_xy[3][3];

	proj_xy[0][0] = 1;
	proj_xy[0][1] = 0;
	proj_xy[0][2] = 0;
	proj_xy[1][0] = 0;
	proj_xy[1][1] = 1;
	proj_xy[1][2] = 0;
	proj_xy[2][0] = 0;
	proj_xy[2][1] = 0;
	proj_xy[2][2] = 0;
	mult_mat_map(proj_xy, map);
}

void	right_left_handed_trafo(t_map *map)
{
	double right_left_trafo[3][3];

	right_left_trafo[0][0] = 1;
	right_left_trafo[0][1] = 0;
	right_left_trafo[0][2] = 0;
	right_left_trafo[1][0] = 0;
	right_left_trafo[1][1] = 1;
	right_left_trafo[1][2] = 0;
	right_left_trafo[2][0] = 0;
	right_left_trafo[2][1] = 0;
	right_left_trafo[2][2] = -1;
	mult_mat_map(right_left_trafo, map);
}

void	mirror_trafo(t_map *map)
{
	double mirror[3][3];

	mirror[0][0] = 1;
	mirror[0][1] = 0;
	mirror[0][2] = 0;
	mirror[1][0] = 0;
	mirror[1][1] = -1;
	mirror[1][2] = 0;
	mirror[2][0] = 0;
	mirror[2][1] = 0;
	mirror[2][2] = 1;
	mult_mat_map(mirror, map);
}

/* apply translation and zooming to all map vecs. */
// TODO add something to xy and zfac ?!?!?!
// TODO make zooming be focused on current map center inside the window ?!?!!
void	trans_zoom_map(t_map *map, double zoom, int trans_x, int trans_y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->vec_map[i][j].x = (double)trans_x + map->vec_map[i][j].x * zoom;
			map->vec_map[i][j].y = (double)trans_y + map->vec_map[i][j].y * zoom;
		}
	}
	map->x_offset += trans_x;
	map->y_offset += trans_y;
	map->zoom *= zoom;
}

/* Scales the z-values in orig_map by zfac. Updates cur_map correspodingly :| */
void scale_height(t_myxvar **mxv, double zfac)
{
	resize_map(*mxv, (*mxv)->orig_map, 1, zfac);
	general_proj(mxv, 0, 0, 0);
}
