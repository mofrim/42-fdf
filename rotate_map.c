/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:38:01 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 12:27:48 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Rotate cur_map about x, y, or z-axis. Only one axis rotation at a time! */
void	rotate_map(t_myxvar *mx, double alpha, double beta, double gamma)
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

/* Generel Projection func used in replay_rotations() after a map height
 * scaling. */
void	rotate_map_replay(t_myxvar *mx, double alpha, double beta, \
		double gamma)
{
	if (alpha)
		rot_map_x(mx->cur_map, alpha);
	else if (beta)
		rot_map_y(mx->cur_map, beta);
	else if (gamma)
		rot_map_z(mx->cur_map, gamma);
}
