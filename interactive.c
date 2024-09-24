/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:16 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/24 06:54:04 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"
#include "mlx.h"

void	handle_arrow_keys(int key, t_myxvar *p);
void	handle_rotation_keys(int key, t_myxvar *p);
void	handle_zoom_keys(int key, t_myxvar *p);
void	handle_quit_destroy_keys(int key, t_myxvar *p);
void	handle_scale_height_keys(int key, t_myxvar *p);
void	handle_center_key(int key, t_myxvar *p);
void	handle_reset_key(int key, t_myxvar *p);
void	handle_debug_key(int key, t_myxvar *p);
void	show_iso_proj(t_myxvar *p);
void	handle_marker_keys(int key, t_myxvar *p);

/* Reset map to origin with '0'. */
// TODO add key for fitting map to (map)-window 'f'
int	key_win1(int key, t_myxvar *p)
{
	// FIXME do i even want this in prod?
	ft_printf("Key in Win1 : %d\n", key);
	if (key == 48)
	{
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->cur_map, 1, -p->cur_map->x_offset, \
				-p->cur_map->y_offset);
		draw_map(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00ff00", *p);
	}
	handle_quit_destroy_keys(key, p);
	handle_rotation_keys(key, p);
	handle_arrow_keys(key, p);
	handle_zoom_keys(key, p);
	handle_scale_height_keys(key, p);
	handle_center_key(key, p);
	handle_reset_key(key, p);
	handle_debug_key(key, p);
	handle_marker_keys(key, p);
	return (0);
}

/* Quit program with 'esc' = 65307. */
void	handle_quit_destroy_keys(int key, t_myxvar *p)
{
	if (key == 65307)
	{
		mlx_destroy_window(p->mlx, p->win);
		if (p->orig_map == p->cur_map)
		{
			free_map(&p->orig_map);
			p->cur_map = NULL;
		}
		else
			free_map(&p->orig_map);
		if (p->cur_map)
			free_map(&p->cur_map);
		free(p->colrmap);
		mlx_destroy_display(p->mlx);
		free(p->mlx);
		free(p);
		exit(0);
	}
}

/* Handle rotation keys.
 *
 * 'q' = 113, rotate about x-axis positively
 * 'a' = 97, rotate about x-axis negatively
 * 'w' = 119, rotate about y-axis positively
 * 's' = 115, rotate about y-axis negatively
 * 'e' = 101, rotate about z-axis positively
 * 'd' = 100, rotate about z-axis negatively
 */
void	handle_rotation_keys(int key, t_myxvar *p)
{

	if (key == 113 || key == 97 || key == 119 || key == 115 || key == 101 || \
			key == 100 || key == 105)
	{
		mlx_clear_window(p->mlx, p->win);
		show_sidebar(p);
		if (key == 113)
			general_proj(&p, ROTSTP, 0, 0);
		if (key == 97)
			general_proj(&p, -ROTSTP, 0, 0);
		if (key == 119)
			general_proj(&p, 0, ROTSTP, 0);
		if (key == 115)
			general_proj(&p, 0, -ROTSTP, 0);
		if (key == 101)
			general_proj(&p, 0, 0, ROTSTP);
		if (key == 100)
			general_proj(&p, 0, 0, -ROTSTP);
		if (key == 105)
			show_iso_proj(p);
		if (p->auto_center_map)
			center_map(p);
		// draw_map(p->cur_map, *p);
		draw_map_color_elev(p->cur_map, *p);
		if (p->show_markers)
			draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
	}
}

void	show_iso_proj(t_myxvar *p)
{
	mlx_clear_window(p->mlx, p->win);
	show_sidebar(p);
	general_proj(&p, -p->cur_map->alpha, -p->cur_map->beta, \
			-p->cur_map->gamma);
	general_proj(&p, -M_PI/7, 0, 0);
	general_proj(&p,0, -M_PI/6, 0);
	general_proj(&p, 0, 0, -M_PI/5);
	center_map(p);
	// draw_map(p->cur_map, *p);
	draw_map_color_elev(p->cur_map, *p);
	if (p->show_markers)
		draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
}

/* Handle map motion on screen through arrow keys.
 * 65364 = Down key, but i want it to move the map up,
 * 65362 = Up key, moves the map down on screen. */
// TODO add hjkl for faster moving
void	handle_arrow_keys(int key, t_myxvar *p)
{
	if (key == 65363 || key == 65361 || key == 65364 || key == 65362)
	{
		mlx_clear_window(p->mlx, p->win);
		show_sidebar(p);
		if (key == 65363)
			trans_zoom_map(p->cur_map, 1, 40, 0);
		if (key == 65361)
			trans_zoom_map(p->cur_map, 1, -40, 0);
		if (key == 65364)
			trans_zoom_map(p->cur_map, 1, 0, 40);
		if (key == 65362)
			trans_zoom_map(p->cur_map, 1, 0, -40);
		// draw_map(p->cur_map, *p);
		draw_map_color_elev(p->cur_map, *p);
		if (p->show_markers)
			draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
	}
}

/* Handle zooming kbd control.
 * '+' = 43 on german keyboard, 61 on us.
 * '-' = 45.
 */
// TODO make zooming experience smoother
void	handle_zoom_keys(int key, t_myxvar *p)
{
	if (key == 61 || key == 43 || key == 45)
	{
		mlx_clear_window(p->mlx, p->win);
		show_sidebar(p);
		if (key == 61 || key == 43)
			trans_zoom_map(p->cur_map, 1.1, 0, 0);
		if (key == 45)
			trans_zoom_map(p->cur_map, 0.9, 0, 0);
		if (p->auto_center_map)
			center_map(p);
		// draw_map(p->cur_map, *p);
		draw_map_color_elev(p->cur_map, *p);
		if (p->show_markers)
			draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
	}
}

void	handle_scale_height_keys(int key, t_myxvar *p)
{
	if (key == 46 || key == 44)
	{
		mlx_clear_window(p->mlx, p->win);
		show_sidebar(p);
		if (key == 46)
			scale_height(&p, 1.1);
		if (key == 44)
			scale_height(&p, 0.9);
		// if (p->auto_center_map)
		// 	center_map(p);
		// draw_map(p->cur_map, *p);
		draw_map_color_elev(p->cur_map, *p);
		if (p->show_markers)
			draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
	}
}

/* 'c' = 99. */
void	handle_center_key(int key, t_myxvar *p)
{
	if (key == 99)
	{
		if (p->auto_center_map)
			p->auto_center_map = 0;
		else
			p->auto_center_map = 1;
		mlx_clear_window(p->mlx, p->win);
		show_sidebar(p);
		draw_map_color_elev(p->cur_map, *p);
		if (p->show_markers)
			draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
	}
}

void	handle_reset_key(int key, t_myxvar *p)
{
	if (key == 114)
	{
		ft_printf("reset!\n");
		mlx_clear_window(p->mlx, p->win);
		show_sidebar(p);
		general_proj(&p, -p->cur_map->alpha, -p->cur_map->beta, \
				-p->cur_map->gamma);
		center_map(p);
		// draw_map(p->cur_map, *p);
		draw_map_color_elev(p->cur_map, *p);
		if (p->show_markers)
			draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
	}
}

/* It's F1 for debug info now. */
void	handle_debug_key(int key, t_myxvar *p)
{
	if (key == 65470)
	{
		ft_printf("\nDEBUG:\n");
		// print_map_without_offset(p->cur_map);
		// ft_printf("x_offset = %d\n", p->cur_map->x_offset);
		// ft_printf("y_offset = %d\n", p->cur_map->y_offset);
		// ft_printf("alpha = %d\n", (int)(10*p->cur_map->alpha));
		// ft_printf("beta = %d\n",(int)(10*p->cur_map->beta));
		// ft_printf("gamma = %d\n", (int)(10*p->cur_map->gamma));
		ft_printf("zdiff = %d\n", p->zdiff);
		ft_printf("cur xyfac = %d\n", (int)p->xyfac);
		ft_printf("orig xyfac = %d\n", (int)p->xyfac);
		ft_printf("cur zfac = %d\n", (int)p->zfac);
		ft_printf("orig zfac = %d\n", (int)p->zfac);
	}
}

/* 'm' = 109, toggle show markers.
 * 'n' = 110, increase marker_size.
 * 'b' = 98,  decrease marker size.*/
void	handle_marker_keys(int key, t_myxvar *p)
{
	if (key == 109 || key == 110 || key == 98)
	{
		if (key == 109)
		{
			if (p->show_markers)
			{
				mlx_clear_window(p->mlx, p->win);
				show_sidebar(p);
				draw_map_color_elev(p->cur_map, *p);
				p->show_markers = 0;
			}
			else
			{
				mlx_clear_window(p->mlx, p->win);
				show_sidebar(p);
				draw_map_color_elev(p->cur_map, *p);
				draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
				p->show_markers = 1;
			}

		}
		if (key == 110)
		{
			p->marker_size++;
			draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
		}
		if (key == 98 && p->marker_size > 1)
		{
			p->marker_size--;
			mlx_clear_window(p->mlx, p->win);
			show_sidebar(p);
			draw_map_color_elev(p->cur_map, *p);
			draw_map_disks_size(p->cur_map, *p, "00ff00", p->marker_size);
		}
	}
}
