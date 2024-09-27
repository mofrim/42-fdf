/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_map_findx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:10:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 12:17:36 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Centers the map by calculating the x-center and the y-center of the current
 * map and then translating the accordingly.
 *
 * The calculation involved: xmid = xmin+(xmax - xmin)/2 = (xmin+xmax)/2. */
void	center_map(t_myxvar *mxv)
{
	int	xmid;
	int	ymid;
	int	win_mid_x;
	int	win_mid_y;

	win_mid_x = (mxv->winsize_x + MAP_AREA_MINX) / 2;
	win_mid_y = mxv->winsize_y / 2;
	xmid = (find_map_x_max(*mxv->cur_map) + find_map_x_min(*mxv->cur_map)) / 2;
	ymid = (find_map_y_max(*mxv->cur_map) + find_map_y_min(*mxv->cur_map)) / 2;
	trans_zoom_map(mxv->cur_map, 1, (win_mid_x - xmid), (win_mid_y - ymid));
}

/* Find map xmin. */
int	find_map_x_min(t_map map)
{
	int		i;
	int		j;
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

/* Find map xmax. */
int	find_map_x_max(t_map map)
{
	int		i;
	int		j;
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
