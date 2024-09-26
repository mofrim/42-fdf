/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_color_elev.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:53:59 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/26 09:17:24 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map_color_elev(t_map *map, t_myxvar mxv)
{
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
			/* one liner map. */
			if (map->rows == 1 && map->cols > 1)
			{
				if (0 <= j && j < map->cols - 1)
					draw_color_line_elev(vmap[0][j], vmap[0][j + 1], mxv);
			}
			else if (map->cols == 1 && map->rows > 1)
			{
				if (0 <= i && i < map->rows - 1)
					draw_color_line_elev(vmap[i][0], vmap[i + 1][0], mxv);
			}
			else if (map->rows == 1 && map->cols == 1)
				return ;
			else
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
}
