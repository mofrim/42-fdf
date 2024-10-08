/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:20 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 12:02:32 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	dupl_copy_map_params(t_map *dupl, t_map *map);

/* Duplicate a map struct. */
t_map	*duplicate_map(t_map *map)
{
	t_map	*dupl;
	int		i;
	int		j;

	dupl = malloc(sizeof(t_map));
	nullcheck(dupl, "duplicate_map().. could not malloc map duplicate");
	dupl_copy_map_params(dupl, map);
	dupl->vec_map = malloc(sizeof(t_vec *) * dupl->rows);
	nullcheck(dupl->vec_map, "duplicate_map().. could not malloc vec_map");
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

/* Free a map struct. */
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
void	resize_map(t_myxvar *mx, t_map *map, double xyfac, double zfac)
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
			map->vec_map[i][j].zo *= zfac;
		}
	}
	mx->xyfac *= xyfac;
	mx->zfac *= zfac;
}

/*  Initial resize of map is winsize_x/(2*cols) for x/y and half of that for z.
 * i want factor * cols = winsize_x/2 => factor = winsize_x/(2*cols) */
void	initial_resize_map(t_myxvar *mx)
{
	double	xyfac;
	double	zfac;

	xyfac = (double)mx->winsize_x / (2 * mx->orig_map->cols);
	zfac = xyfac / 2;
	resize_map(mx, mx->orig_map, xyfac, zfac);
	mx->xyfac = 1;
	mx->zfac = 1;
}
