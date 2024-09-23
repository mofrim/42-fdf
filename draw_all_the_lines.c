/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all_the_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:30:11 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 11:52:57 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO make it 1-param -> only mxv needed here.
// Normify!!!
void	draw_map(t_map *map, t_myxvar mxv)
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
				draw_line(vmap[0][0], vmap[1][0], WHITE2, mxv);
				draw_line(vmap[0][0], vmap[0][1], WHITE2, mxv);
			}
			else if (i == 0 && 0 < j && j < map->cols - 1)
			{
				draw_line(vmap[0][j], vmap[1][j], WHITE2, mxv);
				draw_line(vmap[0][j], vmap[0][j + 1], WHITE2, mxv);
			}
			else if (i == 0 && j == map->cols - 1)
				draw_line(vmap[0][j], vmap[1][j], WHITE2, mxv);

			/* in between. */
			if (i != 0 && i < map->rows - 1 && j == 0)
			{
				draw_line(vmap[i][j], vmap[i][j + 1], WHITE2, mxv);
				draw_line(vmap[i][j], vmap[i + 1][j], WHITE2, mxv);
			}
			else if (i != 0 && i < map->rows - 1 && 0 < j && j < map->cols - 1)
			{
				draw_line(vmap[i][j], vmap[i][j + 1], WHITE2, mxv);
				draw_line(vmap[i][j], vmap[i + 1][j], WHITE2, mxv);
			}
			else if (i != 0 && i < map->rows - 1 && j == map->cols - 1)
				draw_line(vmap[i][j], vmap[i + 1][j], WHITE2, mxv);

			/* last line. */
			if (i == map->rows - 1 && j == 0)
				draw_line(vmap[i][j], vmap[i][j + 1], WHITE2, mxv);
			else if (i == map->rows - 1 && 0 < j && j < map->cols - 1)
				draw_line(vmap[i][j], vmap[i][j + 1], WHITE2, mxv);
		}
	}
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
