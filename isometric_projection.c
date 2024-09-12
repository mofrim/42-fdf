/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 11:25:20 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Added another mirrorring on xy-plane. */
void isometric_proj(t_map *map)
{
	double isoproj_mat[3][3];
	double	one_by_sqrt6;

	one_by_sqrt6 = 1 / sqrt(6);
	isoproj_mat[0][0] = one_by_sqrt6 * sqrt(3);
	isoproj_mat[0][1] = 0;
	isoproj_mat[0][2] = one_by_sqrt6 * (-sqrt(3));
	isoproj_mat[1][0] = one_by_sqrt6;
	isoproj_mat[1][1] = -one_by_sqrt6 * 2;
	isoproj_mat[1][2] = one_by_sqrt6 * 1;
	isoproj_mat[2][0] = 0;
	isoproj_mat[2][1] = 0;
	isoproj_mat[2][2] = 0;
	mult_mat_map(isoproj_mat, map);
}

/* custom proj.
 *
 * normally it is: rotate about 45deg around the vertical (y?! z?!) axis then
 * atan(1/sqrt(2)) about the x axis
 */
void general_proj(t_map *map, double alpha, double beta, double gamma)
{
	double rot_x[3][3];
	double rot_z[3][3];
	double rot_y[3][3];
	double proj_xy[3][3];
	double right_left_trafo[3][3];
	double mirror[3][3];

	rot_x[0][0] = 1;
	rot_x[0][1] = 0;
	rot_x[0][2] = 0;
	rot_x[1][0] = 0;
	rot_x[1][1] = cos(alpha);
	rot_x[1][2] = sin(alpha);
	rot_x[2][0] = 0;
	rot_x[2][1] = -sin(alpha);
	rot_x[2][2] = cos(alpha);

	rot_y[0][0] = cos(beta);
	rot_y[0][1] = -sin(beta);
	rot_y[0][2] = 0;
	rot_y[1][0] = sin(beta);
	rot_y[1][1] = cos(beta);
	rot_y[1][2] = 0;
	rot_y[2][0] = 0;
	rot_y[2][1] = 0;
	rot_y[2][2] = 1;

	rot_z[0][0] = cos(gamma);
	rot_z[0][1] = 0;
	rot_z[0][2] = -sin(gamma);
	rot_z[1][0] = 0;
	rot_z[1][1] = 1;
	rot_z[1][2] = 0;
	rot_z[2][0] = sin(gamma);
	rot_z[2][1] = 0;
	rot_z[2][2] = cos(gamma);

	proj_xy[0][0] = 1;
	proj_xy[0][1] = 0;
	proj_xy[0][2] = 0;
	proj_xy[1][0] = 0;
	proj_xy[1][1] = 1;
	proj_xy[1][2] = 0;
	proj_xy[2][0] = 0;
	proj_xy[2][1] = 0;
	proj_xy[2][2] = 0;

	right_left_trafo[0][0] = 1;
	right_left_trafo[0][1] = 0;
	right_left_trafo[0][2] = 0;
	right_left_trafo[1][0] = 0;
	right_left_trafo[1][1] = 1;
	right_left_trafo[1][2] = 0;
	right_left_trafo[2][0] = 0;
	right_left_trafo[2][1] = 0;
	right_left_trafo[2][2] = -1;

	mirror[0][0] = 1;
	mirror[0][1] = 0;
	mirror[0][2] = 0;
	mirror[1][0] = 0;
	mirror[1][1] = -1;
	mirror[1][2] = 0;
	mirror[2][0] = 0;
	mirror[2][1] = 0;
	mirror[2][2] = 1;

	ft_printf("rot_x:\n");
	print_mat(rot_x);
	ft_printf("rot_z:\n");
	print_mat(rot_z);
	ft_printf("\n");

	ft_printf("rot_x:\n");
	print_mat(rot_x);
	ft_printf("rot_z:\n");
	print_mat(rot_z);
	ft_printf("\n");

	// mult_mat_map(right_left_trafo, map);
	mult_mat_map(rot_x, map);
	mult_mat_map(rot_y, map);
	mult_mat_map(rot_z, map);
	// mult_mat_map(mirror, map);
	mult_mat_map(proj_xy, map);
}
