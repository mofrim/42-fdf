/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_input_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:16 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 14:58:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	kbd_input_handler(int key, t_myxvar *mx)
{
	ft_printf("User pressed key: %d\n", key);
	handle_quit_destroy_keys(key, mx);
	handle_rotation_keys(key, mx);
	handle_arrow_keys(key, mx);
	handle_zoom_keys(key, mx);
	handle_scale_height_keys(key, mx);
	handle_center_key(key, mx);
	handle_reset_key(key, mx);
	handle_debug_key(key, mx);
	handle_marker_keys(key, mx);
	handle_mapstyle_keys(key, mx);
	handle_markerstyle_keys(key, mx);
	return (0);
}

void	redraw_map(t_myxvar *mx)
{
	mlx_clear_window(mx->mlx, mx->win);
	show_sidebar(mx);
	if (mx->auto_center_map)
		center_map(mx);
	if (mx->mapstyle == 1)
		draw_map(mx->cur_map, *mx, draw_line_colr_elev);
	else if (mx->mapstyle == 2)
		draw_map(mx->cur_map, *mx, draw_fat_line_colr_elev);
	else if (mx->mapstyle == 3)
		draw_map(mx->cur_map, *mx, draw_line_nocolr);
	else if (mx->mapstyle == 4)
		draw_map(mx->cur_map, *mx, draw_thick_line_nocolr);
	if (mx->show_markers)
	{
		if (mx->markerstyle == 1)
			draw_map_disks_size(mx->cur_map, *mx, "00ff00", mx->marker_size);
		if (mx->markerstyle == 2)
			draw_map_disks_size_colr_elev(mx->cur_map, *mx, mx->marker_size);
	}
}
