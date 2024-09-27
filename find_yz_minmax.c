/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_yz_minmax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:14:59 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 12:15:32 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Find map ymin. */
int	find_map_y_min(t_map map)
{
	int		i;
	int		j;
	double	ymin;

	i = -1;
	ymin = map.vec_map[0][0].y;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (ymin > map.vec_map[i][j].y)
				ymin = map.vec_map[i][j].y;
	}
	return ((int)ymin);
}

/* Find map ymax. */
int	find_map_y_max(t_map map)
{
	int		i;
	int		j;
	double	ymax;

	i = -1;
	ymax = map.vec_map[0][0].y;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (ymax < map.vec_map[i][j].y)
				ymax = map.vec_map[i][j].y;
	}
	return ((int)ymax);
}

/* Find map zmin. */
int	find_map_z_min(t_map map)
{
	int		i;
	int		j;
	double	zmin;

	i = -1;
	zmin = map.vec_map[0][0].z;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (zmin > map.vec_map[i][j].z)
				zmin = map.vec_map[i][j].z;
	}
	return ((int)zmin);
}

/* Find map zmax. */
int	find_map_z_max(t_map map)
{
	int		i;
	int		j;
	double	zmax;

	i = -1;
	zmax = map.vec_map[0][0].z;
	while (++i < map.rows)
	{
		j = -1;
		while (++j < map.cols)
			if (zmax < map.vec_map[i][j].z)
				zmax = map.vec_map[i][j].z;
	}
	return ((int)zmax);
}
