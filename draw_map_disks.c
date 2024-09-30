/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_disks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:19:37 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 12:17:37 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Draw a disk, which is a filled circle, around pixel p. */
void	draw_disk(t_pxl p, int radius, int colr, t_myxvar mxv)
{
	int	i;
	int	j;

	i = -1;
	while (++i < radius)
	{
		j = -1;
		while (++j < sqrt(radius * radius - i * i))
		{
			mlx_pixel_put(mxv.mlx, mxv.win, p.x - i, p.y + j, colr);
			mlx_pixel_put(mxv.mlx, mxv.win, p.x - i, p.y - j, colr);
			mlx_pixel_put(mxv.mlx, mxv.win, p.x + i, p.y + j, colr);
			mlx_pixel_put(mxv.mlx, mxv.win, p.x + i, p.y - j, colr);
		}
	}
}

/* Draw the map with placing disks of certain size at every point. As color for
 * the disks use the color member in the t_vec struct. */
void	draw_map_disks_size(t_map *map, t_myxvar myxvar, int size)
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
				draw_disk(p, size, map->vec_map[i][j].colr, myxvar);
		}
	}
}

/* Draw the map with placing disks of certain size at every point. As color for
 * the disks use the elevation color. */
void	draw_map_disks_size_colr_elev(t_map *map, t_myxvar mx, int size)
{
	int		i;
	int		j;
	t_pxl	p;
	int		z;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			p.x = map->vec_map[i][j].x;
			p.y = map->vec_map[i][j].y;
			z = map->vec_map[i][j].zo;
			if (MAP_AREA_MINX <= p.x && p.x <= WINX && 0 <= p.y && p.y <= WINY)
				draw_disk(p, size, get_elev_colr(z, mx), mx);
		}
	}
}
