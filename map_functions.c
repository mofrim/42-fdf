/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:20 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 14:17:15 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*duplicate_map(t_map *map)
{
	t_map	*dupl;
	int		i;
	int		j;

	dupl = malloc(sizeof(t_map));
	if (!dupl)
		error_exit();
	dupl->cols = map->cols;
	dupl->rows = map->rows;
	dupl->x_offset = map->x_offset;
	dupl->y_offset = map->y_offset;
	dupl->zoom = map->zoom;
	dupl->alpha = map->alpha;
	dupl->beta = map->beta;
	dupl->gamma = map->gamma;
	dupl->xyfac = map->xyfac;
	dupl->zfac = map->zfac;
	dupl->vec_map = malloc(sizeof(t_vec *) * dupl->rows);
	if (!dupl->vec_map)
		error_exit();
	i = -1;
	while (++i < dupl->rows)
	{
		j = -1;
		dupl->vec_map[i] = malloc(sizeof(t_vec) * dupl->cols);
		if (!dupl->vec_map[i])
			error_exit();
		while (++j < dupl->cols)
			dupl->vec_map[i][j] = map->vec_map[i][j];
	}
	return (dupl);
}

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
			ft_printf("(%2d,%2d,%2d,%8d) ", (int)map->vec_map[i][j].x, \
					(int)map->vec_map[i][j].y, (int)map->vec_map[i][j].z, \
					(int)map->vec_map[i][j].colr);
		ft_printf("\n");
	}
}

void	print_map_without_offset(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
			ft_printf("(%2d,%2d,%2d) ", (int)map->vec_map[i][j].x - \
					map->x_offset, (int)map->vec_map[i][j].y - map->y_offset, \
					(int)map->vec_map[i][j].z);
		ft_printf("\n");
	}
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
void	resize_map(t_map *map, double xyfac, double zfac)
{
	int	i;
	int j;

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
	map->xyfac *= xyfac;
	map->zfac *= zfac;
}

/*  Initial resize of map is winsize_x/(2*cols) for x/y and half of that for z.
 * i want factor * cols = winsize_x/2 => factor = winsize_x/(2*cols) */
void initial_resize_map(t_myxvar *mxv, double xyfac, double zfac)
{
	double	factor;
	int		cols;

	cols = mxv->orig_map->cols;
	if (xyfac == 0)
		xyfac = (double)mxv->winsize_x / (2 * cols);
	if (zfac == 0)
		zfac = xyfac / 2;
	mxv->orig_map->xyfac = xyfac;
	mxv->orig_map->zfac = zfac;
	// mxv->orig_map->xyfac = 1;
	// mxv->orig_map->zfac = 1;
	resize_map(mxv->orig_map, xyfac, zfac);
}
