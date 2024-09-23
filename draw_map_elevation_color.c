/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_elevation_color.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:53:59 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 15:04:27 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// 0 -> diff/2 gen colrs between 0000ff and 00ff00
// diff/2 -> diff gen colrs between 00ff00 and ff0000
int	*generate_colrmap(t_myxvar mxv)
{
	int	*cmap;
	int	colr;
	int	i;
	int	N;

	cmap = malloc(sizeof(int) * mxv.zdiff + 1);
	i = 0;
	N = mxv.zdiff / 2;
	while (i <= N)
	{
		cmap[i] = (((int)(255 * (double)i/N)) << 8) | ((int)(255 * (1.0-(double)i/N)));
		i++;
	}
	i = 0;
	while (i <= N)
	{
		cmap[N + i] = (((int)(255 * (double)i/N)) << 16) | (((int)(255 * (1.0-(double)i/N))) << 8) ;
		i++;
	}
	return (cmap);
}

int	get_pixel_colr_elev(int	z, t_myxvar mxv)
{
	return (mxv.colrmap[z - mxv.zmin]);
}

// FIXMEEEEEEEE
// uff!! the z-values must come from the orig_map! because due to projections i
// get randomly negative z-values here.
// SOLUTION added reset_zvalues after projection.
void	draw_color_line_elev(t_vec a, t_vec b, t_myxvar mxv)
{
	double	dx;
	double	dy;
	double	dz;
	int		N;
	int		i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (fabs(dx) >= fabs(dy))
		N = fabs(dx);
	else
		N = fabs(dy);

	dx = dx / (double)N;
	dy = dy / (double)N;
	dz = (b.z - a.z) / (double)N;
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(mxv.mlx, mxv.win, a.x, a.y, get_pixel_colr_elev(a.z, mxv));
		a.x += dx;
		a.y += dy;
		a.z += dz;
		i++;
	}
}

void	draw_map_color_elev(t_map *map, t_myxvar mxv)
{
	t_line		line;
	t_vec		**vmap;
	int			i;
	int			j;

	vmap = map->vec_map;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			/* first line. */
			if (i == 0 && j == 0)
			{
				draw_color_line_elev(vmap[0][0], vmap[1][0], mxv);
				draw_color_line_elev(vmap[0][0], vmap[0][1], mxv);
			}
			else if (i == 0 && 0 < j && j < map->cols - 1)
			{
				draw_color_line_elev(vmap[0][j], vmap[1][j], mxv);
				draw_color_line_elev(vmap[0][j], vmap[0][j + 1], mxv);
			}
			else if (i == 0 && j == map->cols - 1)
				draw_color_line_elev(vmap[0][j], vmap[1][j], mxv);

			/* in between. */
			if (i != 0 && i < map->rows - 1 && j == 0)
			{
				draw_color_line_elev(vmap[i][j], vmap[i][j + 1], mxv);
				draw_color_line_elev(vmap[i][j], vmap[i + 1][j], mxv);
			}
			else if (i != 0 && i < map->rows - 1 && 0 < j && j < map->cols - 1)
			{
				draw_color_line_elev(vmap[i][j], vmap[i][j + 1], mxv);
				draw_color_line_elev(vmap[i][j], vmap[i + 1][j], mxv);
			}
			else if (i != 0 && i < map->rows - 1 && j == map->cols - 1)
				draw_color_line_elev(vmap[i][j], vmap[i + 1][j], mxv);

			/* last line. */
			if (i == map->rows - 1 && j == 0)
				draw_color_line_elev(vmap[i][j], vmap[i][j + 1], mxv);
			else if (i == map->rows - 1 && 0 < j && j < map->cols - 1)
				draw_color_line_elev(vmap[i][j], vmap[i][j + 1], mxv);
		}
	}
}
