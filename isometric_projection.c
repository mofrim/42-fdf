/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/19 08:08:33 by fmaurer          ###   ########.fr       */
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
	t_map_props_bak mpbak;

	mpbak.old_zoom = (*mxv)->cur_map->zoom;
	mpbak.old_xoff = (*mxv)->cur_map->x_offset;
	mpbak.old_yoff = (*mxv)->cur_map->y_offset;
	mpbak.old_alpha = (*mxv)->cur_map->alpha;
	mpbak.old_beta = (*mxv)->cur_map->beta;
	mpbak.old_gamma = (*mxv)->cur_map->gamma;
	free_map(&(*mxv)->cur_map);
	(*mxv)->cur_map = duplicate_map((*mxv)->orig_map);
	(*mxv)->cur_map->alpha = mpbak.old_alpha;
	(*mxv)->cur_map->beta = mpbak.old_beta;
	(*mxv)->cur_map->gamma = mpbak.old_gamma;
	rot_map_x((*mxv)->cur_map, alpha);
	rot_map_y((*mxv)->cur_map, beta);
	rot_map_z((*mxv)->cur_map, gamma);
	proj_map_to_xy((*mxv)->cur_map);
	trans_zoom_map((*mxv)->cur_map, mpbak.old_zoom, mpbak.old_xoff, mpbak.old_yoff);
}
