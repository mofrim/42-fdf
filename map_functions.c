/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:20 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/14 10:03:38 by fmaurer          ###   ########.fr       */
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
	// ft_printf("dupl map = %p\n", dupl);
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
			ft_printf("(%2d,%2d,%2d) ", (int)map->vec_map[i][j].x, \
					(int)map->vec_map[i][j].y, (int)map->vec_map[i][j].z);
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
void	resize_map(t_map *map, double factor)
{
	int	i;
	int j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->vec_map[i][j].x *= factor;
			map->vec_map[i][j].y *= factor;
			map->vec_map[i][j].z *= factor;
		}
	}
}

/* i want factor * cols = winsize_x/2 => factor = winsize_x/(2*cols) */
void initial_resize_map(t_myxvar *mxv)
{
	double	factor;
	int		cols;

	cols = mxv->orig_map->cols;
	factor = (double)mxv->winsize_x / (2 * cols);
	resize_map(mxv->orig_map, factor);
}
