/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_color_elev.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:53:59 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/26 16:57:50 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO dont need this anymore... mod interactive.c accordingly
void	draw_map_color_elev(t_map *map, t_myxvar mxv)
{
	draw_map(map, mxv, draw_line_colr_elev);
}
