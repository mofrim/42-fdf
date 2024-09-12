/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:53:08 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 07:10:18 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* apply translation and zooming to all map vecs. */
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
			map->vec_map[i][j].x = trans_x + map->vec_map[i][j].x * zoom;
			map->vec_map[i][j].y = trans_y + map->vec_map[i][j].y * zoom;
		}
	}
}

/* this function should only draw some thick points at the map grid. eventually
 * this will be done in 3d. */
// void draw_map_points(t_map *map, int zoom_level, char *colr, t_myxvar myxvar)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;
//
// 	i = -1;
// 	while (++i < map->rows)
// 	{
// 		j = -1;
// 		while (++j < map->cols)
// 		{
// 			// x = myxvar.winsize_x/2 + map->vec_map[i][j].x * zoom_level - \
// 			// 	map->cols/2 * zoom_level;
// 			x = myxvar.winsize_x/2 + map->vec_map[i][j].x * zoom_level - map->cols/4*zoom_level;
//
// 			// y = myxvar.winsize_y/2 + map->vec_map[i][j].y * zoom_level - \
// 			// 	map->rows/2 * zoom_level;
// 			y = myxvar.winsize_y/2 + map->vec_map[i][j].y * zoom_level - \
// 				map->rows/5 * zoom_level;
//
// 			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y, rgb_to_int(colr));
// 			mlx_pixel_put(myxvar.mlx, myxvar.win, x-1, y, rgb_to_int(colr));
// 			mlx_pixel_put(myxvar.mlx, myxvar.win, x+1, y, rgb_to_int(colr));
// 			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y-1, rgb_to_int(colr));
// 			mlx_pixel_put(myxvar.mlx, myxvar.win, x, y+1, rgb_to_int(colr));
// 		}
// 	}
// }

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
