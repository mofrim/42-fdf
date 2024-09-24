/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereographic_proj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:06:56 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/24 22:28:35 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	stereo_proj(t_myxvar *mxv)
{
	double	r;
	int		i;
	int		j;
	t_vec	**smap;

	r = mxv->zmax + 1;
	free_map(&mxv->cur_map);
	mxv->cur_map = duplicate_map(mxv->orig_map);
	smap = mxv->cur_map->vec_map;
	i = 0;
	while (i < mxv->cur_map->rows)
	{
		j = 0;
		while (j < mxv->cur_map->cols)
		{
			smap[i][j].x = smap[i][j].x / (r - smap[i][j].z);
			smap[i][j].y = smap[i][j].y / (r - smap[i][j].z);
			j++;
		}
		i++;
	}
}

void	cylindr_proj(t_myxvar *mxv)
{
	double	r;
	double	theta;
	int		i;
	int		j;
	t_vec	**smap;

	r = mxv->zmax + 1;
	free_map(&mxv->cur_map);
	mxv->cur_map = duplicate_map(mxv->orig_map);
	smap = mxv->cur_map->vec_map;
	i = 0;
	while (i < mxv->cur_map->rows)
	{
		j = 0;
		while (j < mxv->cur_map->cols)
		{
			r = sqrt(smap[i][j].x * smap[i][j].x + smap[i][j].y * smap[i][j].y);
			theta = atan2(smap[i][j].y, smap[i][j].x);
			smap[i][j].x = r * cos(theta);
			smap[i][j].y = smap[i][j].z;
			j++;
		}
		i++;
	}
}
