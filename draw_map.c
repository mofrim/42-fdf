/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:12:23 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 15:23:54 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Helper functions. */
static void	draw_first_mapline(t_map *map, void (*line_draw_func) (t_vec, \
			t_vec, t_myxvar), t_myxvar mxv);
static void	draw_amidst_mapline(t_map *map, int i, void (*line_draw_func)\
		(t_vec, t_vec, t_myxvar), t_myxvar mxv);
static void	draw_last_mapline(t_map *map, int i, void (*line_draw_func)(t_vec, \
			t_vec, t_myxvar), t_myxvar mxv);
static void	draw_one_rowcol_maps(t_map *map, void (*line_draw_func)(t_vec, \
			t_vec, t_myxvar), t_myxvar mxv);

/* Generic map drawing function. line_draw_func() is function used for drawing
 * the lines of the map. Allows for flexible styling. */
void	draw_map(t_map *map, t_myxvar mxv, void (*line_draw_func)\
		(t_vec, t_vec, t_myxvar))
{
	int			i;

	if (map->rows == 1 || map->cols == 1)
		draw_one_rowcol_maps(map, line_draw_func, mxv);
	else
	{
		i = -1;
		while (++i < map->rows)
		{
			if (i == 0)
				draw_first_mapline(map, line_draw_func, mxv);
			else if (0 < i && i < map->rows - 1)
				draw_amidst_mapline(map, i, line_draw_func, mxv);
			else
				draw_last_mapline(map, i, line_draw_func, mxv);
		}
	}
}

void	draw_one_rowcol_maps(t_map *map, void (*line_draw_func)(t_vec, t_vec, \
			t_myxvar), t_myxvar mxv)
{
	int		k;
	t_vec	**vmap;

	vmap = map->vec_map;
	k = -1;
	if (map->rows == 1 && map->cols > 1)
	{
		while (++k < map->cols)
			if (0 <= k && k < map->cols - 1)
				line_draw_func(vmap[0][k], vmap[0][k + 1], mxv);
	}
	else if (map->rows > 1 && map->cols == 1)
	{
		while (++k < map->rows)
			if (0 <= k && k < map->rows - 1)
				line_draw_func(vmap[k][0], vmap[k + 1][0], mxv);
	}
	else
		return ;
}

void	draw_first_mapline(t_map *map, void (*line_draw_func)(t_vec, t_vec, \
			t_myxvar), t_myxvar mxv)
{
	int		j;
	t_vec	**vmap;

	vmap = map->vec_map;
	j = -1;
	while (++j < map->cols)
	{
		if (j == 0)
		{
			line_draw_func(vmap[0][0], vmap[1][0], mxv);
			line_draw_func(vmap[0][0], vmap[0][1], mxv);
		}
		else if (0 < j && j < map->cols - 1)
		{
			line_draw_func(vmap[0][j], vmap[1][j], mxv);
			line_draw_func(vmap[0][j], vmap[0][j + 1], mxv);
		}
		else if (j == map->cols - 1)
			line_draw_func(vmap[0][j], vmap[1][j], mxv);
	}
}

void	draw_amidst_mapline(t_map *map, int i, void (*line_draw_func)(t_vec, \
			t_vec, t_myxvar), t_myxvar mxv)
{
	int		j;
	t_vec	**vmap;

	vmap = map->vec_map;
	j = -1;
	while (++j < map->cols)
	{
		if (j == 0)
		{
			line_draw_func(vmap[i][j], vmap[i][j + 1], mxv);
			line_draw_func(vmap[i][j], vmap[i + 1][j], mxv);
		}
		else if (0 < j && j < map->cols - 1)
		{
			line_draw_func(vmap[i][j], vmap[i][j + 1], mxv);
			line_draw_func(vmap[i][j], vmap[i + 1][j], mxv);
		}
		else
			line_draw_func(vmap[i][j], vmap[i + 1][j], mxv);
	}
}

void	draw_last_mapline(t_map *map, int i, void (*line_draw_func)(t_vec, \
			t_vec, t_myxvar), t_myxvar mxv)
{
	int		j;
	t_vec	**vmap;

	vmap = map->vec_map;
	j = -1;
	while (++j < map->cols)
	{
		if (j == 0)
			line_draw_func(vmap[i][j], vmap[i][j + 1], mxv);
		else if (0 < j && j < map->cols - 1)
			line_draw_func(vmap[i][j], vmap[i][j + 1], mxv);
	}
}
