/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_trafos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:44:31 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 11:09:16 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* apply translation and zooming to all map vecs. */
void	trans_zoom_map(t_map *map, double zoom, int trans_x, int trans_y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->vec_map[i][j].x = (double)trans_x + map->vec_map[i][j].x * \
						zoom;
			map->vec_map[i][j].y = (double)trans_y + map->vec_map[i][j].y * \
						zoom;
		}
	}
	map->x_offset += trans_x;
	map->y_offset += trans_y;
	map->zoom *= zoom;
}

static void	replay_rotations(t_myxvar *mx)
{
	t_anglst	*al;

	al = mx->anglst;
	while (al)
	{
		rotate_map_replay(mx, al->a, al->b, al->g);
		al = al->next;
	}
}

/* Scales the z-values in orig_map by zfac. Updates cur_map correspodingly :| */
void	scale_height(t_myxvar *mx, double zfac)
{
	t_map_props_bak	mpbak;

	mpbak.old_zoom = mx->cur_map->zoom;
	mpbak.old_xoff = mx->cur_map->x_offset;
	mpbak.old_yoff = mx->cur_map->y_offset;
	mpbak.old_alpha = mx->cur_map->alpha;
	mpbak.old_beta = mx->cur_map->beta;
	mpbak.old_gamma = mx->cur_map->gamma;
	free_map(&mx->cur_map);
	resize_map(mx, mx->orig_map, 1, zfac);
	mx->cur_map = duplicate_map(mx->orig_map);
	replay_rotations(mx);
	trans_zoom_map(mx->cur_map, mpbak.old_zoom, mpbak.old_xoff, \
			mpbak.old_yoff);
}

void	right_left_handed_trafo(t_map *map)
{
	double	right_left_trafo[3][3];

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

void	mirror_trafo(t_map *map)
{
	double	mirror[3][3];

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
