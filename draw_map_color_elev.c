/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_color_elev.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:53:59 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/26 15:25:14 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_first_mapline(t_vec **vmap, int cols, t_myxvar mxv);
static void	draw_amidst_mapline(t_vec **vmap, int i, int cols, t_myxvar mxv);
static void	draw_last_mapline(t_vec **vmap, int rows, int cols, t_myxvar mxv);
static void	draw_one_rowcol_maps(t_vec **vmap, int rows, int cols, t_myxvar mxv);

void	draw_map_color_elev(t_map *map, t_myxvar mxv)
{
	t_vec		**vmap;
	int			i;

	vmap = map->vec_map;
	if (map->rows == 1 || map->cols == 1)
		draw_one_rowcol_maps(vmap, map->rows, map->cols, mxv);
	else
	{
		i = -1;
		while (++i < map->rows)
		{
			if (i == 0)
				draw_first_mapline(vmap, map->cols, mxv);
			else if (0 < i && i < map->rows - 1)
				draw_amidst_mapline(vmap, i, map->cols, mxv);
			else
				draw_last_mapline(vmap, i, map->cols, mxv);
		}
	}
}

void	draw_last_mapline(t_vec **vmap, int i, int cols, t_myxvar mxv)
{
	int	j;

	j = -1;
	while (++j < cols)
	{
		if (j == 0)
			draw_color_line_elev(vmap[i][j], vmap[i][j + 1], mxv);
		else if (0 < j && j < cols - 1)
			draw_color_line_elev(vmap[i][j], vmap[i][j + 1], mxv);
	}
}

void	draw_amidst_mapline(t_vec **vmap, int i, int cols, t_myxvar mxv)
{
	int	j;

	j = -1;
	while (++j < cols)
	{
		if (j == 0)
		{
			draw_color_line_elev(vmap[i][j], vmap[i][j + 1], mxv);
			draw_color_line_elev(vmap[i][j], vmap[i + 1][j], mxv);
		}
		else if (0 < j && j < cols - 1)
		{
			draw_color_line_elev(vmap[i][j], vmap[i][j + 1], mxv);
			draw_color_line_elev(vmap[i][j], vmap[i + 1][j], mxv);
		}
		else
			draw_color_line_elev(vmap[i][j], vmap[i + 1][j], mxv);
	}
}

void	draw_first_mapline(t_vec **vmap, int cols, t_myxvar mxv)
{
	int	j;

	j = -1;
	while (++j < cols)
	{
		if (j == 0)
		{
			draw_color_line_elev(vmap[0][0], vmap[1][0], mxv);
			draw_color_line_elev(vmap[0][0], vmap[0][1], mxv);
		}
		else if (0 < j && j < cols - 1)
		{
			draw_color_line_elev(vmap[0][j], vmap[1][j], mxv);
			draw_color_line_elev(vmap[0][j], vmap[0][j + 1], mxv);
		}
		else if (j == cols - 1)
			draw_color_line_elev(vmap[0][j], vmap[1][j], mxv);
	}
}

void	draw_one_rowcol_maps(t_vec **vmap, int rows, int cols, t_myxvar mxv)
{
	int	k;

	k = -1;
	if (rows == 1 && cols > 1)
	{
		while (++k < cols)
			if (0 <= k && k < cols - 1)
				draw_color_line_elev(vmap[0][k], vmap[0][k + 1], mxv);
	}
	else if (rows > 1 && cols == 1)
	{
		while (++k < rows)
			if (0 <= k && k < rows - 1)
				draw_color_line_elev(vmap[k][0], vmap[k + 1][0], mxv);
	}
	else
		return ;
}
