/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:53:08 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/10 23:09:34 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* this function should only draw some thick points at the map grid. eventually
 * this will be done in 3d. */
void draw_map_points(t_map *map, int zoom_level, char *colr, t_myxvar myxvar)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			x = myxvar.winsize_x/2 + map->vec_map[i][j].x * zoom_level - \
				map->cols/2 * zoom_level;
			y = myxvar.winsize_y/2 + map->vec_map[i][j].y * zoom_level - \
				map->rows/2 * zoom_level;
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x-1, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x+1, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y-1, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y+1, rgb_to_int(colr));
		}
	}
}
