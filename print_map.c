/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 00:19:17 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 16:54:28 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Print map to console. */
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

/* Print map without color member. */
void	print_map_nocolr(t_map *map)
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

/* Print map without offset. For debugging. */
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
