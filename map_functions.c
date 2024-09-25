/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:20 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/26 00:28:52 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	dupl_copy_map_params(t_map *dupl, t_map *map);

t_map	*duplicate_map(t_map *map)
{
	t_map	*dupl;
	int		i;
	int		j;

	dupl = malloc(sizeof(t_map));
	nullcheck(dupl, "duplicate_map().. could not malloc map duplicate");
	dupl->vec_map = malloc(sizeof(t_vec *) * dupl->rows);
	nullcheck(dupl->vec_map, "duplicate_map().. could not malloc vec_map");
	dupl_copy_map_params(dupl, map);
	i = -1;
	while (++i < dupl->rows)
	{
		j = -1;
		dupl->vec_map[i] = malloc(sizeof(t_vec) * dupl->cols);
		nullcheck(dupl->vec_map[i], "duplicate_map().. malloc vec_map row");
		while (++j < dupl->cols)
			dupl->vec_map[i][j] = map->vec_map[i][j];
	}
	return (dupl);
}

void	dupl_copy_map_params(t_map *dupl, t_map *map)
{
	dupl->cols = map->cols;
	dupl->rows = map->rows;
	dupl->x_offset = map->x_offset;
	dupl->y_offset = map->y_offset;
	dupl->zoom = map->zoom;
	dupl->alpha = map->alpha;
	dupl->beta = map->beta;
	dupl->gamma = map->gamma;
}

void	free_map(t_map **map)
{
	int	i;

	i = -1;
	while (++i < (*map)->rows)
		free((*map)->vec_map[i]);
	free((*map)->vec_map);
	free(*map);
	*map = NULL;
}

/* Multiply every x,y,z coord of the map by a constant factor. */
void	resize_map(t_myxvar *mxv, t_map *map, double xyfac, double zfac)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->vec_map[i][j].x *= xyfac;
			map->vec_map[i][j].y *= xyfac;
			map->vec_map[i][j].z *= zfac;
		}
	}
	mxv->xyfac *= xyfac;
	mxv->zfac *= zfac;
}

/*  Initial resize of map is winsize_x/(2*cols) for x/y and half of that for z.
 * i want factor * cols = winsize_x/2 => factor = winsize_x/(2*cols) */
void	initial_resize_map(t_myxvar *mxv, double xyfac, double zfac)
{
	double	factor;
	int		cols;

	cols = mxv->orig_map->cols;
	if (xyfac == 0)
		xyfac = (double)mxv->winsize_x / (2 * cols);
	if (zfac == 0)
		zfac = xyfac / 2;
	resize_map(mxv, mxv->orig_map, xyfac, zfac);
	mxv->xyfac = 1;
	mxv->zfac = 1;
}
