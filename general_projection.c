/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_projection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 08:58:29 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	reset_zvalues(t_map *cur_map, t_map *orig_map);

/* Do general rotation by alpha around x, beta around y, gamma around z-axis.
 * The rotation will be applied to the numerically unspoiled orig_map. After
 * applying the rotations the map will be restored to its last position and zoom
 * status in the window. Finally all z-values will be (falsely) reset to their
 * orig_map values in order to get elevation-coloring right.
 *
 * Isometric projection would be: rotate about 45deg around the vertical (y?!
 * z?!) axis then atan(1/sqrt(2)) about the x axis.
 */
void	general_proj(t_myxvar *mx, double alpha, double beta, double gamma)
{
	t_map_props_bak	mpbak;

	mpbak.old_zoom = mx->cur_map->zoom;
	mpbak.old_xoff = mx->cur_map->x_offset;
	mpbak.old_yoff = mx->cur_map->y_offset;
	mpbak.old_alpha = mx->cur_map->alpha;
	mpbak.old_beta = mx->cur_map->beta;
	mpbak.old_gamma = mx->cur_map->gamma;
	free_map(&mx->cur_map);
	mx->cur_map = duplicate_map(mx->orig_map);
	mx->cur_map->alpha = mpbak.old_alpha;
	mx->cur_map->beta = mpbak.old_beta;
	mx->cur_map->gamma = mpbak.old_gamma;
	rot_map_x(mx->cur_map, alpha);
	rot_map_y(mx->cur_map, beta);
	rot_map_z(mx->cur_map, gamma);
	trans_zoom_map(mx->cur_map, mpbak.old_zoom, mpbak.old_xoff, \
			mpbak.old_yoff);
	reset_zvalues(mx->cur_map, mx->orig_map);
}

/* Helper func for resetting z-values of cur_map to the ones from orig_map. */
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
