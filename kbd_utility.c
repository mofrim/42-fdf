/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:42:49 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 12:03:10 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		anglstclear(&p->anglst);
		mlx_destroy_display(p->mlx);
		free(p->mlx);
		free(p);
		exit(0);
	}
}

/* It's F1 for debug info now. */
void	handle_debug_key(int key, t_myxvar *p)
{
	if (key == 65470)
	{
		ft_printf("\nDEBUG:\n");
		print_map_without_offset(p->cur_map);
		ft_printf("x_offset = %d\n", p->cur_map->x_offset);
		ft_printf("y_offset = %d\n", p->cur_map->y_offset);
		ft_printf("alpha = %d\n", (int)(10 * p->cur_map->alpha));
		ft_printf("beta = %d\n", (int)(10 * p->cur_map->beta));
		ft_printf("gamma = %d\n", (int)(10 * p->cur_map->gamma));
		ft_printf("zdiff = %d\n", p->zdiff);
		ft_printf("cur xyfac = %d\n", (int)p->xyfac);
		ft_printf("orig xyfac = %d\n", (int)p->xyfac);
		ft_printf("cur zfac = %d\n", (int)p->zfac);
		ft_printf("orig zfac = %d\n", (int)p->zfac);
	}
}

/* Reset map to orig. */
void	reset_map(t_myxvar *mx)
{
	anglstclear(&mx->anglst);
	free_map(&mx->cur_map);
	resize_map(mx, mx->orig_map, 1, 1.0 / mx->zfac);
	mx->cur_map = duplicate_map(mx->orig_map);
}

/* 'r' = 114, reset map to center and default view. */
void	handle_reset_key(int key, t_myxvar *mx)
{
	if (key == 114)
	{
		ft_printf("reset!\n");
		reset_map(mx);
		center_map(mx);
		redraw_map(mx);
	}
}

/* Scale height.
 * '.' = 46, increase zfac
 * ',' = 44, decrease zfac
 */
void	handle_scale_height_keys(int key, t_myxvar *mx)
{
	if (key == 46 || key == 44)
	{
		if (key == 46)
			scale_height(mx, 1.1);
		if (key == 44)
			scale_height(mx, 0.9);
		redraw_map(mx);
	}
}
