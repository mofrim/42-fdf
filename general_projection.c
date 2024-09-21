/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_projection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/21 14:39:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* custom proj.
 *
 * normally it is: rotate about 45deg around the vertical (y?! z?!) axis then
 * atan(1/sqrt(2)) about the x axis
 *
 * FIXME remove unneccessary double pointer
 *
 * TODO i have to do the already existing rotations first!!! and then the new
 * one!!! omg! how do i keep track of what was done so far?!?! and in which
 * order?!?
 * O - M - G!!! do i really have to keep track of all rotations been done using a
 * linked list ?!?
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
