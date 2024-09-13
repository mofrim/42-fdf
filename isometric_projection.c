/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/13 08:23:37 by fmaurer          ###   ########.fr       */
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
 *
 * TODO rewrite to do rotations in-place on orig_map. Translations, zooming and
 * displaying will be done on cur_map.
 */
void general_proj(t_myxvar **mxv, double alpha, double beta, double gamma)
{
	t_map	*tmp;

	// do rotations on orig_map
	rot_map_x((*mxv)->orig_map, alpha);
	ft_printf("in proj:\n");
	print_map((*mxv)->orig_map);
	rot_map_y((*mxv)->orig_map, beta);
	rot_map_z((*mxv)->orig_map, gamma);

	// do projection and translation on cur_map
	tmp = duplicate_map((*mxv)->cur_map);
	free_map(&(*mxv)->cur_map);
	(*mxv)->cur_map = duplicate_map((*mxv)->orig_map);
	// (*mxv)->cur_map->y_offset = tmp->y_offset;
	// (*mxv)->cur_map->x_offset = tmp->x_offset;
	// (*mxv)->cur_map->zoom = tmp->zoom;
	// (*mxv)->cur_map->alpha = tmp->alpha;
	// (*mxv)->cur_map->beta = tmp->beta;
	// (*mxv)->cur_map->gamma = tmp->gamma;
	proj_map_to_xy((*mxv)->cur_map);
	trans_zoom_map((*mxv)->cur_map, (*mxv)->cur_map->zoom, (*mxv)->cur_map->x_offset, (*mxv)->cur_map->y_offset);
}
