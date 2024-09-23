/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:10:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 16:39:02 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"


/* to be used with cur_map. */
int	find_map_x_min(t_map map)
{
	int	i;
	int	j;
	double	xmin;

	i = -1;
	xmin = map.vec_map[0][0].x;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (xmin > map.vec_map[i][j].x)
				xmin = map.vec_map[i][j].x;
	}
	return ((int)xmin);
}

/* to be used with cur_map. */
int	find_map_x_max(t_map map)
{
	int	i;
	int	j;
	double	xmax;

	i = -1;
	xmax = map.vec_map[0][0].x;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (xmax < map.vec_map[i][j].x)
				xmax = map.vec_map[i][j].x;
	}
	return ((int)xmax);
}

/* to be used with cur_map. */
int	find_map_y_min(t_map map)
{
	int	i;
	int	j;
	double	ymin;

	i = -1;
	ymin = map.vec_map[0][0].y;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (ymin > map.vec_map[i][j].y)
				ymin = map.vec_map[i][j].y;
	}
	return ((int)ymin);
}

/* to be used with cur_map. */
int	find_map_y_max(t_map map)
{
	int	i;
	int	j;
	double	ymax;

	i = -1;
	ymax = map.vec_map[0][0].y;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (ymax < map.vec_map[i][j].y)
				ymax = map.vec_map[i][j].y;
	}
	return ((int)ymax);
}

/* to be used with cur_map. */
int	find_map_z_min(t_map map)
{
	int	i;
	int	j;
	double	zmin;

	i = -1;
	zmin = map.vec_map[0][0].z;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (zmin > map.vec_map[i][j].z)
				zmin = map.vec_map[i][j].z;
	}
	return ((int)zmin);
}

/* to be used with cur_map. */
int	find_map_z_max(t_map map)
{
	int	i;
	int	j;
	double	zmax;

	i = -1;
	zmax = map.vec_map[0][0].z;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (zmax < map.vec_map[i][j].z)
				zmax = map.vec_map[i][j].z;
	}
	return ((int)zmax);
}

/* Centers the map by calculating the x-center and the y-center of the current
 * map and then translating the accordingly.
 *
 * The calculation involved: xmid = xmin+(xmax - xmin)/2 = (xmin+xmax)/2. */
void	center_map(t_myxvar *mxv)
{
	int	xmid;
	int	ymid;
	int	win_mid_x;
	int win_mid_y;

	win_mid_x = (mxv->winsize_x + MAP_AREA_MINX) / 2;
	win_mid_y = mxv->winsize_y / 2;
	xmid = (find_map_x_max(*mxv->cur_map) + find_map_x_min(*mxv->cur_map)) / 2;
	ymid = (find_map_y_max(*mxv->cur_map) + find_map_y_min(*mxv->cur_map)) / 2;
	trans_zoom_map(mxv->cur_map, 1, (win_mid_x - xmid), (win_mid_y - ymid));
}
