/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_xyz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:28:35 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 16:55:52 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Multiply map by rotation matrix around x-axis by angl. */
void	rot_map_x(t_map *map, double angl)
{
	double	rot_x[3][3];

	map->alpha += angl;
	rot_x[0][0] = 1;
	rot_x[0][1] = 0;
	rot_x[0][2] = 0;
	rot_x[1][0] = 0;
	rot_x[1][1] = cos(map->alpha);
	rot_x[1][2] = -sin(map->alpha);
	rot_x[2][0] = 0;
	rot_x[2][1] = sin(map->alpha);
	rot_x[2][2] = cos(map->alpha);
	mult_mat_map(rot_x, map);
}

/* Multiply map by rotation matrix around y-axis by angl. */
void	rot_map_y(t_map *map, double angl)
{
	double	rot_y[3][3];

	map->beta += angl;
	rot_y[0][0] = cos(map->beta);
	rot_y[0][1] = 0;
	rot_y[0][2] = -sin(map->beta);
	rot_y[1][0] = 0;
	rot_y[1][1] = 1;
	rot_y[1][2] = 0;
	rot_y[2][0] = sin(map->beta);
	rot_y[2][1] = 0;
	rot_y[2][2] = cos(map->beta);
	mult_mat_map(rot_y, map);
}

/* Multiply map by rotation matrix around z-axis by angl. */
void	rot_map_z(t_map *map, double angl)
{
	double	rot_z[3][3];

	map->gamma += angl;
	rot_z[0][0] = cos(map->gamma);
	rot_z[0][1] = -sin(map->gamma);
	rot_z[0][2] = 0;
	rot_z[1][0] = sin(map->gamma);
	rot_z[1][1] = cos(map->gamma);
	rot_z[1][2] = 0;
	rot_z[2][0] = 0;
	rot_z[2][1] = 0;
	rot_z[2][2] = 1;
	mult_mat_map(rot_z, map);
}
