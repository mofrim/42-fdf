/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/19 07:32:21 by fmaurer          ###   ########.fr       */
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
void general_proj(t_myxvar **mxv, double alpha, double beta, double gamma)
{
	t_map	*tmp;
	double	old_zoom;
	int		old_xoff;
	int		old_yoff;

	// TODO... rewrite so that we always keep an untouched version of
	// initial map in some corner. the rotations should be added to a persistent
	// angle variable so that the resulting rotation can always be performed
	// using the numerically unspoiled initial_map.
	//
	// TODO... another one: create a function for measuring the distance along
	// the first row. i.e. dist(map[0][0] and map [0][2]) for mini.fdf and print
	// that for investigatin the shrink.

	// do rotations on orig_map
	rot_map_x((*mxv)->orig_map, alpha);
	rot_map_y((*mxv)->orig_map, beta);
	rot_map_z((*mxv)->orig_map, gamma);

	// DEBUG
	ft_printf("(*mxv)->cur_map->zoom = %d, (*mxv)->cur_map->x_offset = %d, (*mxv)->cur_map->y_offset = %d\n", (int)(*mxv)->cur_map->zoom, (*mxv)->cur_map->x_offset, (*mxv)->cur_map->y_offset);

	// do projection and translation on cur_map
	old_zoom = (*mxv)->cur_map->zoom;
	old_xoff = (*mxv)->cur_map->x_offset;
	old_yoff = (*mxv)->cur_map->y_offset;
	tmp = duplicate_map((*mxv)->cur_map);
	free_map(&(*mxv)->cur_map);
	(*mxv)->cur_map = duplicate_map((*mxv)->orig_map);
	(*mxv)->cur_map->x_offset = 0;
	(*mxv)->cur_map->y_offset = 0;
	(*mxv)->cur_map->zoom = 1;
	proj_map_to_xy((*mxv)->cur_map);
	trans_zoom_map((*mxv)->cur_map, old_zoom, old_xoff, old_yoff);
}
