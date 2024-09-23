/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_disks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:19:37 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 16:10:16 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* y <= sqrt(R² - x²) */
t_pxlcloud	*calc_disk_cloud(int x, int y, int radius)
{
	t_pxlcloud	*pc;
	int			i;
	int			j;

	pc = NULL;
	i = -1;
	while (++i < radius)
	{
		j = -1;
		while (++j < sqrt(radius * radius - i * i))
		{
			pxcl_add_back(&pc, pxcl_new(x - i, y + j));
			pxcl_add_back(&pc, pxcl_new(x - i, y - j));
			pxcl_add_back(&pc, pxcl_new(x + i, y + j));
			pxcl_add_back(&pc, pxcl_new(x + i, y - j));
		}
	}
	return (pc);
}

/* Draw a filled circle at (x, y) with radius. */
// void	draw_disk(t_pxl p, int radius, char *colr, t_myxvar mxv)
// {
// 	t_pxlcloud	*pxcl;
// 	t_pxlcloud	*pxcl_bak;
//
// 	pxcl = calc_disk_cloud(p.x, p.y, radius);
// 	pxcl_bak = pxcl;
// 	while (pxcl)
// 	{
// 		mlx_pixel_put(mxv.mlx, mxv.win, (int)pxcl->x, (int)pxcl->y, \
// 				rgb_to_int(colr));
// 		pxcl = pxcl->next;
// 	}
// 	pxcl_clear(&pxcl_bak);
// 	free(pxcl_bak);
// }
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
