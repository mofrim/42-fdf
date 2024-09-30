/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_xyz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:28:35 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 11:19:00 by fmaurer          ###   ########.fr       */
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
	rot_x[1][1] = cos(angl);
	rot_x[1][2] = sin(angl);
	rot_x[2][0] = 0;
	rot_x[2][1] = -sin(angl);
	rot_x[2][2] = cos(angl);
	mult_mat_map(rot_x, map);
}

/* Multiply map by rotation matrix around y-axis by angl. */
void	rot_map_y(t_map *map, double angl)
{
	double	rot_y[3][3];

	map->beta += angl;
	rot_y[0][0] = cos(angl);
	rot_y[0][1] = 0;
	rot_y[0][2] = -sin(angl);
	rot_y[1][0] = 0;
	rot_y[1][1] = 1;
	rot_y[1][2] = 0;
	rot_y[2][0] = sin(angl);
	rot_y[2][1] = 0;
	rot_y[2][2] = cos(angl);
	mult_mat_map(rot_y, map);
}

/* Multiply map by rotation matrix around z-axis by angl. */
void	rot_map_z(t_map *map, double angl)
{
	double	rot_z[3][3];

	map->gamma += angl;
	rot_z[0][0] = cos(angl);
	rot_z[0][1] = sin(angl);
	rot_z[0][2] = 0;
	rot_z[1][0] = -sin(angl);
	rot_z[1][1] = cos(angl);
	rot_z[1][2] = 0;
	rot_z[2][0] = 0;
	rot_z[2][1] = 0;
	rot_z[2][2] = 1;
	mult_mat_map(rot_z, map);
}


/**
 * This one really works now.
 *
 * 1) mirror z-values
 * 2) rot_x by atan(1/sqrt(2)) * rot_y by pi/4
 * 3) rot_z by 30deg (sin(pi/3) = sqrt(3)/2)
 */
void	rot_map_iso(t_map *map)
{
	double	rot[3][3];
	double	rot2[3][3];
	double	rot3[3][3];

	rot3[0][0] = 1;
	rot3[0][1] = 0;
	rot3[0][2] = 0;
	rot3[1][0] = 0;
	rot3[1][1] = 1;
	rot3[1][2] = 0;
	rot3[2][0] = 0;
	rot3[2][1] = 0;
	rot3[2][2] = -1;
	mult_mat_map(rot3, map);

	rot[0][0] = sqrt(3);
	rot[0][1] = 0;
	rot[0][2] = -sqrt(3);
	rot[1][0] = 1;
	rot[1][1] = 2;
	rot[1][2] = 1;
	rot[2][0] = sqrt(2);
	rot[2][1] = -sqrt(2);
	rot[2][2] = sqrt(2);
	mult_mat_by_scalar(&rot, 1/sqrt(6));
	mult_mat_map(rot, map);

	rot2[0][0] = 0.5;
	rot2[0][1] = sqrt(3)/2;
	rot2[0][2] = 0;
	rot2[1][0] = -sqrt(3)/2;
	rot2[1][1] = 0.5;
	rot2[1][2] = 0;
	rot2[2][0] = 0;
	rot2[2][1] = 0;
	rot2[2][2] = 1;
	mult_mat_map(rot2, map);
}

// void	rot_map_iso(t_map *map)
// {
// 	double	rot[3][3];
//
// 	rot[0][0] = sqrt(3);
// 	rot[0][1] = 0;
// 	rot[0][2] = -sqrt(3);
// 	rot[1][0] = sqrt(2);
// 	rot[1][1] = -sqrt(2);
// 	rot[1][2] = sqrt(2);
// 	rot[2][0] = -1;
// 	rot[2][1] = -2;
// 	rot[2][2] = -1;
// 	mult_mat_by_scalar(&rot, 1/sqrt(6));
// 	mult_mat_map(rot, map);
// }

/* looks good... but no 120deg angles :( */
// void	rot_map_iso(t_map *map)
// {
// 	double	rot[3][3];
//
// 	rot[0][0] = sqrt(3);
// 	rot[0][1] = -sqrt(3);
// 	rot[0][2] = 0;
// 	rot[1][0] = sqrt(2);
// 	rot[1][1] = sqrt(2);
// 	rot[1][2] = sqrt(2);
// 	rot[2][0] = -1;
// 	rot[2][1] = -1;
// 	rot[2][2] = 2;
// 	mult_mat_by_scalar(&rot, 1/sqrt(6));
// 	mult_mat_map(rot, map);
// }


// void	rot_map_iso(t_map *map)
// {
// 	double	rot[3][3];
//
// 	rot[0][0] = sqrt(3);
// 	rot[0][1] = -sqrt(3);
// 	rot[0][2] = 0;
// 	rot[1][0] = sqrt(2);
// 	rot[1][1] = sqrt(2);
// 	rot[1][2] = -sqrt(2);
// 	rot[2][0] = -1;
// 	rot[2][1] = -1;
// 	rot[2][2] = -2;
// 	mult_mat_by_scalar(&rot, 1/sqrt(6));
// 	mult_mat_map(rot, map);
// }
