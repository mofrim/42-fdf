/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_projection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 08:43:24 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	reset_zvalues(t_map *cur_map, t_map *orig_map);

/* custom proj.
 *
 * normally it is: rotate about 45deg around the vertical (y?! z?!) axis then
 * atan(1/sqrt(2)) about the x axis
 *
 * FIXME remove unneccessary double pointer
 */
void	general_proj(t_myxvar **mxv, double alpha, double beta, double gamma)
{
	t_map_props_bak	mpbak;

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
	trans_zoom_map((*mxv)->cur_map, mpbak.old_zoom, mpbak.old_xoff, \
			mpbak.old_yoff);
	reset_zvalues((*mxv)->cur_map, (*mxv)->orig_map);
}

static void	reset_zvalues(t_map *cur_map, t_map *orig_map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < cur_map->rows)
	{
		j = -1;
		while (++j < cur_map->cols)
			cur_map->vec_map[i][j].z = orig_map->vec_map[i][j].z;
	}
}
