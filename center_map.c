/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:10:22 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/20 16:37:33 by fmaurer          ###   ########.fr       */
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

	win_mid_x = mxv->winsize_x / 2;
	win_mid_y = mxv->winsize_y / 2;

	xmid = (find_map_x_max(*mxv->cur_map) + find_map_x_min(*mxv->cur_map)) / 2;
	ymid = (find_map_y_max(*mxv->cur_map) + find_map_y_min(*mxv->cur_map)) / 2;

	// DEBUG
	// ft_printf("xmax = %d, xmin %d\n", find_map_x_max(*mxv->cur_map), find_map_x_min(*mxv->cur_map));
	// ft_printf("xmid = %d, ymid = %d\n", xmid, ymid);
	// ft_printf("win_mid_x = %d, win_mid_y = %d\n", \
	// 		mxv->winsize_x / 2, mxv->winsize_y / 2);
	// ft_printf("moving, x: %d, y: %d\n", win_mid_x - xmid, win_mid_y - ymid);
	// ft_printf("off_x = %d, off_y = %d\n", mxv->cur_map->x_offset, mxv->cur_map->y_offset);

	trans_zoom_map(mxv->cur_map, 1, (win_mid_x - xmid), (win_mid_y - ymid));
}
