/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:16 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/21 15:11:23 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_arrow_keys(int key, t_myxvar *p);
void	handle_rotation_keys(int key, t_myxvar *p);
void	handle_zoom_keys(int key, t_myxvar *p);
void	handle_quit_destroy_keys(int key, t_myxvar *p);
void	handle_scale_height_keys(int key, t_myxvar *p);
void	handle_center_key(int key, t_myxvar *p);
void	handle_menu_key(int key, t_myxvar *p);
void	handle_reset_key(int key, t_myxvar *p);
void	handle_debug_key(int key, t_myxvar *p);
;
/* Reset map to origin with '0'. */
int	key_win1(int key, t_myxvar *p)
{
	ft_printf("Key in Win1 : %d\n", key);
	if (key == 48)
	{
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->cur_map, 1, -p->cur_map->x_offset, \
				-p->cur_map->y_offset);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00ff00", *p);
	}
	handle_quit_destroy_keys(key, p);
	handle_rotation_keys(key, p);
	handle_arrow_keys(key, p);
	handle_zoom_keys(key, p);
	handle_scale_height_keys(key, p);
	handle_center_key(key, p);
	handle_menu_key(key, p);
	handle_reset_key(key, p);
	handle_debug_key(key, p);
	return (0);
}

/* Quit program with 'q' = 113, or just destroy window with 'w' = 119. */
void	handle_quit_destroy_keys(int key, t_myxvar *p)
{
	if (key == 113)
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
		free(p->mlx);
		free(p);
		exit(0);
	}
	if (key == 119)
		mlx_destroy_window(p->mlx, p->win);
}

/* Handle rotation keys.
 *
 * 'x' = 120, rotate about x-axis positively
 * 's' = 115, rotate about x-axis negatively
 * 'y' = 121, rotate about y-axis positively
 * 'a' = 97, rotate about y-axis negatively
 * 'z' = 122, rotate about z-axis positively
 * 'h' = 104, rotate about z-axis negatively
 */
void	handle_rotation_keys(int key, t_myxvar *p)
{
	if (key == 120 || key == 115 || key == 121 || key == 97 || key == 122 || \
			key == 104 || key == 105)
	{
		mlx_clear_window(p->mlx, p->win);
		if (key == 120)
			general_proj(&p, ROTSTP, 0, 0);
		if (key == 115)
			general_proj(&p, -ROTSTP, 0, 0);
		if (key == 121)
			general_proj(&p, 0, ROTSTP, 0);
		if (key == 97)
			general_proj(&p, 0, -ROTSTP, 0);
		if (key == 122)
			general_proj(&p, 0, 0, ROTSTP);
		if (key == 104)
			general_proj(&p, 0, 0, -ROTSTP);
		if (key == 105)
			general_proj(&p, atan(1/sqrt(2)), 0, M_PI/4);
		if (p->auto_center_map)
			center_map(p);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_disks_size(p->cur_map, *p, "00ff00", 5);
	}
}

/* Handle map motion on screen through arrow keys.
 * 65364 = Down key, but i want it to move the map up,
 * 65362 = Up key, moves the map down on screen. */
void	handle_arrow_keys(int key, t_myxvar *p)
{
	if (key == 65363 || key == 65361 || key == 65364 || key == 65362)
	{
		mlx_clear_window(p->mlx, p->win);
		if (key == 65363)
			trans_zoom_map(p->cur_map, 1, 20, 0);
		if (key == 65361)
			trans_zoom_map(p->cur_map, 1, -20, 0);
		if (key == 65364)
			trans_zoom_map(p->cur_map, 1, 0, 20);
		if (key == 65362)
			trans_zoom_map(p->cur_map, 1, 0, -20);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_disks_size(p->cur_map, *p, "00ff00", 5);
	}
}

/* Handle zooming kbd control.
 * '+' = 43 on german keyboard, 61 on us.
 * '-' = 45.
 */
void	handle_zoom_keys(int key, t_myxvar *p)
{
	if (key == 61 || key == 43 || key == 45)
	{
		mlx_clear_window(p->mlx, p->win);
		if (key == 61 || key == 43)
			trans_zoom_map(p->cur_map, 1.1, 0, 0);
		if (key == 45)
			trans_zoom_map(p->cur_map, 0.9, 0, 0);
		if (p->auto_center_map)
			center_map(p);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_disks_size(p->cur_map, *p, "00ff00", 5);
	}
}

void	handle_scale_height_keys(int key, t_myxvar *p)
{
	if (key == 46 || key == 44)
	{
		mlx_clear_window(p->mlx, p->win);
		if (key == 46)
			scale_height(&p, 1.1);
		if (key == 44)
			scale_height(&p, 0.9);
		if (p->auto_center_map)
			center_map(p);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_disks_size(p->cur_map, *p, "00ff00", 5);
	}
}

/* 'c' = 99. */
void	handle_center_key(int key, t_myxvar *p)
{
	if (key == 99)
	{
		mlx_clear_window(p->mlx, p->win);
		center_map(p);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_disks_size(p->cur_map, *p, "00ff00", 5);
	}
}

void	handle_menu_key(int key, t_myxvar *p)
{
	if (key == 109)
	{
		if (!p->menu_visible)
		{
			show_menu(p);
			p->menu_visible = 1;
		}
		else
		{
			mlx_clear_window(p->mlx, p->win);
			draw_all_the_lines(p->cur_map, *p);
			draw_map_disks_size(p->cur_map, *p, "00ff00", 5);
			p->menu_visible = 0;
		}
	}
}

void	handle_reset_key(int key, t_myxvar *p)
{
	if (key == 114)
	{
		ft_printf("reset!\n");
		mlx_clear_window(p->mlx, p->win);
		general_proj(&p, -p->cur_map->alpha, -p->cur_map->beta, \
				-p->cur_map->gamma);
		center_map(p);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_disks_size(p->cur_map, *p, "00ff00", 5);
	}
}

void	handle_debug_key(int key, t_myxvar *p)
{
	if (key == 100)
	{
		ft_printf("\nDEBUG:\n");
		print_map_without_offset(p->cur_map);
		ft_printf("x_offset = %d\n", p->cur_map->x_offset);
		ft_printf("y_offset = %d\n", p->cur_map->y_offset);
		ft_printf("alpha = %d\n", (int)(10*p->cur_map->alpha));
		ft_printf("beta = %d\n",(int)(10*p->cur_map->beta));
		ft_printf("gamma = %d\n", (int)(10*p->cur_map->gamma));
	}
}
