/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_trafo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:10:38 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 12:11:48 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Handle rotation keys.
 *
 * 'q' = 113, rotate about x-axis positively
 * 'a' = 97, rotate about x-axis negatively
 * 'w' = 119, rotate about y-axis positively
 * 's' = 115, rotate about y-axis negatively
 * 'e' = 101, rotate about z-axis positively
 * 'd' = 100, rotate about z-axis negatively
 */
void	handle_rotation_keys(int key, t_myxvar *mx)
{
	if (key == 113 || key == 97 || key == 119 || key == 115 || key == 101 || \
			key == 100 || key == 105)
	{
		if (key == 113)
			rotate_map(mx, M_PI / 12, 0, 0);
		if (key == 97)
			rotate_map(mx, -M_PI / 12, 0, 0);
		if (key == 119)
			rotate_map(mx, 0, M_PI / 12, 0);
		if (key == 115)
			rotate_map(mx, 0, -M_PI / 12, 0);
		if (key == 101)
			rotate_map(mx, 0, 0, M_PI / 12);
		if (key == 100)
			rotate_map(mx, 0, 0, -M_PI / 12);
		if (key == 105)
			show_iso_proj(mx);
		redraw_map(mx);
	}
}

void	show_iso_proj(t_myxvar *mx)
{
	reset_map(mx);
	rotate_map(mx, 0, M_PI/4, 0);
	rotate_map(mx, atan(1/sqrt(2)), 0, 0);
	rotate_map(mx, 0, 0, M_PI/3);
	redraw_map(mx);
}

/* Handle map motion on screen through arrow keys.
 * 65364 = Down key, but i want it to move the map up,
 * 65362 = Up key, moves the map down on screen. */
void	handle_arrow_keys(int key, t_myxvar *mx)
{
	if (key == 65363 || key == 65361 || key == 65364 || key == 65362)
	{
		if (key == 65363)
			trans_zoom_map(mx->cur_map, 1, 40, 0);
		if (key == 65361)
			trans_zoom_map(mx->cur_map, 1, -40, 0);
		if (key == 65364)
			trans_zoom_map(mx->cur_map, 1, 0, 40);
		if (key == 65362)
			trans_zoom_map(mx->cur_map, 1, 0, -40);
		redraw_map(mx);
	}
}

/* Handle zooming kbd control.
 * '+' = 43 on german keyboard, 61 on us.
 * '-' = 45.
 */
// TODO make zooming experience smoother
void	handle_zoom_keys(int key, t_myxvar *mx)
{
	if (key == 61 || key == 43 || key == 45)
	{
		if (key == 61 || key == 43)
			trans_zoom_map(mx->cur_map, 1.1, 0, 0);
		if (key == 45)
			trans_zoom_map(mx->cur_map, 0.9, 0, 0);
		redraw_map(mx);
	}
}

/* 'c' = 99. */
void	handle_center_key(int key, t_myxvar *mx)
{
	if (key == 99)
	{
		if (mx->auto_center_map)
			mx->auto_center_map = 0;
		else
			mx->auto_center_map = 1;
		redraw_map(mx);
	}
}
