/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_trafo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:10:38 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 08:35:07 by fmaurer          ###   ########.fr       */
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
		mlx_clear_window(mx->mlx, mx->win);
		if (key == 113)
			general_proj(mx, M_PI / 12, 0, 0);
		if (key == 97)
			general_proj(mx, -M_PI / 12, 0, 0);
		if (key == 119)
			general_proj(mx, 0, M_PI / 12, 0);
		if (key == 115)
			general_proj(mx, 0, -M_PI / 12, 0);
		if (key == 101)
			general_proj(mx, 0, 0, M_PI / 12);
		if (key == 100)
			general_proj(mx, 0, 0, -M_PI / 12);
		if (key == 105)
			show_iso_proj(mx);
		redraw_map(mx);
	}
}

void	show_iso_proj(t_myxvar *mx)
{
	mlx_clear_window(mx->mlx, mx->win);
	general_proj(mx, -mx->cur_map->alpha, -mx->cur_map->beta, \
			-mx->cur_map->gamma);
	general_proj(mx, -M_PI / 7, 0, 0);
	general_proj(mx, 0, -M_PI / 6, 0);
	general_proj(mx, 0, 0, -M_PI / 5);
	redraw_map(mx);
}

/* Handle map motion on screen through arrow keys.
 * 65364 = Down key, but i want it to move the map up,
 * 65362 = Up key, moves the map down on screen. */
// TODO add hjkl for faster moving
void	handle_arrow_keys(int key, t_myxvar *mx)
{
	if (key == 65363 || key == 65361 || key == 65364 || key == 65362)
	{
		mlx_clear_window(mx->mlx, mx->win);
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
		mlx_clear_window(mx->mlx, mx->win);
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
		mlx_clear_window(mx->mlx, mx->win);
		redraw_map(mx);
	}
}
