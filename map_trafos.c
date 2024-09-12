/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_trafos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:44:31 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 19:45:10 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rot_map_x(t_map *map, double angl)
{
	double rot_x[3][3];

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

void	rot_map_y(t_map *map, double angl)
{
	double rot_y[3][3];

	rot_y[0][0] = cos(angl);
	rot_y[0][1] = -sin(angl);
	rot_y[0][2] = 0;
	rot_y[1][0] = sin(angl);
	rot_y[1][1] = cos(angl);
	rot_y[1][2] = 0;
	rot_y[2][0] = 0;
	rot_y[2][1] = 0;
	rot_y[2][2] = 1;
	mult_mat_map(rot_y, map);
}

void	rot_map_z(t_map *map, double angl)
{
	double rot_z[3][3];

	rot_z[0][0] = cos(angl);
	rot_z[0][1] = 0;
	rot_z[0][2] = -sin(angl);
	rot_z[1][0] = 0;
	rot_z[1][1] = 1;
	rot_z[1][2] = 0;
	rot_z[2][0] = sin(angl);
	rot_z[2][1] = 0;
	rot_z[2][2] = cos(angl);
	mult_mat_map(rot_z, map);
}

void	proj_map_to_xy(t_map *map)
{
	double proj_xy[3][3];

	proj_xy[0][0] = 1;
	proj_xy[0][1] = 0;
	proj_xy[0][2] = 0;
	proj_xy[1][0] = 0;
	proj_xy[1][1] = 1;
	proj_xy[1][2] = 0;
	proj_xy[2][0] = 0;
	proj_xy[2][1] = 0;
	proj_xy[2][2] = 0;
	mult_mat_map(proj_xy, map);
}

void	right_left_handed_trafo(t_map *map)
{
	double right_left_trafo[3][3];

	right_left_trafo[0][0] = 1;
	right_left_trafo[0][1] = 0;
	right_left_trafo[0][2] = 0;
	right_left_trafo[1][0] = 0;
	right_left_trafo[1][1] = 1;
	right_left_trafo[1][2] = 0;
	right_left_trafo[2][0] = 0;
	right_left_trafo[2][1] = 0;
	right_left_trafo[2][2] = -1;
	mult_mat_map(right_left_trafo, map);
}

void	mirro_trafo(t_map *map)
{
	double mirror[3][3];

	mirror[0][0] = 1;
	mirror[0][1] = 0;
	mirror[0][2] = 0;
	mirror[1][0] = 0;
	mirror[1][1] = -1;
	mirror[1][2] = 0;
	mirror[2][0] = 0;
	mirror[2][1] = 0;
	mirror[2][2] = 1;
	mult_mat_map(mirror, map);
}
