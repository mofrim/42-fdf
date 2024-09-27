/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:10:44 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/26 08:32:33 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* NOTE Obsolete implementation approach.
 */
int	interpolate_color(int start, int end, double step);

typedef struct s_line
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
}	t_line;

void	draw_color_line(t_vec a, t_vec b, t_myxvar mxv)
{
	double	dx;
	double	dy;
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
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(mxv.mlx, mxv.win, a.x, a.y, \
				interpolate_color(a.colr, b.colr, ((double)i)/N));
		a.x += dx;
		a.y += dy;
		i++;
	}
}

int	interpolate_color(int start, int end, double step)
{
	int	rgb_start[3];
	int	rgb_end[3];
	int	current_colr;

	if (start == end)
		return (start);
	current_colr = 0;
	current_colr |= rgb_start[0] + (int)((rgb_end[0] - rgb_start[0]) * step);
	current_colr <<= 8;
	current_colr |= rgb_start[1] + (int)((rgb_end[1] - rgb_start[1]) * step);
	current_colr <<= 8;
	current_colr |= rgb_start[2] + (int)((rgb_end[2] - rgb_start[2]) * step);
	return (current_colr);
}

void	draw_map_color(t_map *map, t_myxvar mxv)
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
				draw_color_line(vmap[0][0], vmap[1][0], mxv);
				draw_color_line(vmap[0][0], vmap[0][1], mxv);
			}
			else if (i == 0 && 0 < j && j < map->cols - 1)
			{
				draw_color_line(vmap[0][j], vmap[1][j], mxv);
				draw_color_line(vmap[0][j], vmap[0][j + 1], mxv);
			}
			else if (i == 0 && j == map->cols - 1)
				draw_color_line(vmap[0][j], vmap[1][j], mxv);

			/* in between. */
			if (i != 0 && i < map->rows - 1 && j == 0)
			{
				draw_color_line(vmap[i][j], vmap[i][j + 1], mxv);
				draw_color_line(vmap[i][j], vmap[i + 1][j], mxv);
			}
			else if (i != 0 && i < map->rows - 1 && 0 < j && j < map->cols - 1)
			{
				draw_color_line(vmap[i][j], vmap[i][j + 1], mxv);
				draw_color_line(vmap[i][j], vmap[i + 1][j], mxv);
			}
			else if (i != 0 && i < map->rows - 1 && j == map->cols - 1)
				draw_color_line(vmap[i][j], vmap[i + 1][j], mxv);

			/* last line. */
			if (i == map->rows - 1 && j == 0)
				draw_color_line(vmap[i][j], vmap[i][j + 1], mxv);
			else if (i == map->rows - 1 && 0 < j && j < map->cols - 1)
				draw_color_line(vmap[i][j], vmap[i][j + 1], mxv);
		}
	}
}

