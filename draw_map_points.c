/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:53:08 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 23:51:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_map_points(t_map *map, char *colr, t_myxvar myxvar)
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
			x = map->vec_map[i][j].x;
			y = map->vec_map[i][j].y;
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x-1, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x+1, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y-1, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y+1, rgb_to_int(colr));
		}
	}
}

void draw_map_fat_points(t_map *map, char *colr, t_myxvar myxvar)
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
			x = map->vec_map[i][j].x;
			y = map->vec_map[i][j].y;
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x-1, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x-2, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x+1, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x+2, y, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y-1, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y-2, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y+1, rgb_to_int(colr));
			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y+2, rgb_to_int(colr));
		}
	}
}
