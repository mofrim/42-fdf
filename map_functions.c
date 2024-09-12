/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:20 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 19:38:54 by fmaurer          ###   ########.fr       */
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
