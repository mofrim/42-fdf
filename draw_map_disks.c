/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_disks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:19:37 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 17:20:10 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_disk(t_pxl p, int radius, char *colr, t_myxvar mxv)
{
	int	i;
	int	j;

	i = -1;
	while (++i < radius)
	{
		j = -1;
		while (++j < sqrt(radius * radius - i * i))
		{
			mlx_pixel_put(mxv.mlx, mxv.win, p.x - i, p.y + j, rgb_to_int(colr));
			mlx_pixel_put(mxv.mlx, mxv.win, p.x - i, p.y - j, rgb_to_int(colr));
			mlx_pixel_put(mxv.mlx, mxv.win, p.x + i, p.y + j, rgb_to_int(colr));
			mlx_pixel_put(mxv.mlx, mxv.win, p.x + i, p.y - j, rgb_to_int(colr));
		}
	}
}

void	draw_map_disks_size(t_map *map, t_myxvar myxvar, char *colr, int size)
{
	int		i;
	int		j;
	t_pxl	p;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			p.x = map->vec_map[i][j].x;
			p.y = map->vec_map[i][j].y;
			if (MAP_AREA_MINX <= p.x && p.x <= WINX && 0 <= p.y && p.y <= WINY)
				draw_disk(p, size, colr, myxvar);
		}
	}
}
