/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_projection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 11:06:20 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


/* Rotate cur_map about x, y, or z-axis. Only one axis rotation at a time! */
// FIXME rename!
void	general_proj(t_myxvar *mx, double alpha, double beta, double gamma)
{
	if (alpha)
	{
		rot_map_x(mx->cur_map, alpha);
		anglst_add_back(&mx->anglst, anglstnew(alpha, 0, 0));
	}
	else if (beta)
	{
		rot_map_y(mx->cur_map, beta);
		anglst_add_back(&mx->anglst, anglstnew(0, beta, 0));
	}
	else if (gamma)
	{
		rot_map_z(mx->cur_map, gamma);
		anglst_add_back(&mx->anglst, anglstnew(0, 0, gamma));
	}
}


//// Old version...
//
// void	general_proj(t_myxvar *mx, double alpha, double beta, double gamma)
// {
// 	t_map_props_bak	mpbak;
//
// 	mpbak.old_zoom = mx->cur_map->zoom;
// 	mpbak.old_xoff = mx->cur_map->x_offset;
// 	mpbak.old_yoff = mx->cur_map->y_offset;
// 	mpbak.old_alpha = mx->cur_map->alpha;
// 	mpbak.old_beta = mx->cur_map->beta;
// 	mpbak.old_gamma = mx->cur_map->gamma;
// 	free_map(&mx->cur_map);
// 	mx->cur_map = duplicate_map(mx->orig_map);
// 	mx->cur_map->alpha = mpbak.old_alpha;
// 	mx->cur_map->beta = mpbak.old_beta;
// 	mx->cur_map->gamma = mpbak.old_gamma;
// 	rot_map_x(mx->cur_map, alpha);
// 	rot_map_y(mx->cur_map, beta);
// 	rot_map_z(mx->cur_map, gamma);
// 	trans_zoom_map(mx->cur_map, mpbak.old_zoom, mpbak.old_xoff,
// 			mpbak.old_yoff);
// 	reset_zvalues(mx->cur_map, mx->orig_map);
// }

/* Generel Projection func used in replay_rotations() after a map height
 * scaling. */
void	general_proj_replay(t_myxvar *mx, double alpha, double beta, \
		double gamma)
{
	if (alpha)
		rot_map_x(mx->cur_map, alpha);
	else if (beta)
		rot_map_y(mx->cur_map, beta);
	else if (gamma)
		rot_map_z(mx->cur_map, gamma);
}

void	iso_proj(t_myxvar *mx)
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
	rot_map_iso(mx->cur_map);
	trans_zoom_map(mx->cur_map, mpbak.old_zoom, mpbak.old_xoff, \
			mpbak.old_yoff);
}
