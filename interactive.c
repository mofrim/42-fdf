/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:16 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/13 22:13:32 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Down 65364
 * Up 65362
 */
int key_win1(int key,t_myxvar *p)
{

	printf("Key in Win1 : %d\n",key);
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
		exit(0);
	}
	// w
	if (key == 119)
		mlx_destroy_window(p->mlx, p->win);
	// x
	if (key == 120)
	{
		mlx_clear_window(p->mlx, p->win);
		general_proj(&p, 0.1, 0, 0);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// s
	if (key == 115)
	{
		mlx_clear_window(p->mlx, p->win);
		general_proj(&p, -0.1, 0, 0);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// y
	if (key == 121)
	{
		mlx_clear_window(p->mlx, p->win);
		general_proj(&p, -0.2, 0, 0);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// a
	if (key == 97)
	{
		mlx_clear_window(p->mlx, p->win);
		general_proj(&p, 0.2, 0, 0);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// z
	if (key == 122)
	{
		mlx_clear_window(p->mlx, p->win);
		general_proj(&p, 0, 0, 0.2);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// h
	if (key == 104)
	{
		mlx_clear_window(p->mlx, p->win);
		general_proj(&p, 0, 0, -0.2);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	if (key == 65363)
	{
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->cur_map, 1, 10, 0);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	if (key == 65361)
	{
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->cur_map, 1, -10, 0);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// Down key, but up
	if (key == 65364)
	{
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->cur_map, 1, 0, 10);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// Up key, but down
	if (key == 65362)
	{
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->cur_map, 1, 0, -10);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// + = 43 on german keyboard, 61 on us
	if (key == 61 || key == 43)
	{
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->cur_map, 2, 0, 0);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	// + = 45
	if (key == 45)
	{
		mlx_clear_window(p->mlx, p->win);
		trans_zoom_map(p->cur_map, 0.5, 0, 0);
		draw_all_the_lines(p->cur_map, *p);
		draw_map_fat_points(p->cur_map, "00FF00", *p);
	}
	return (0);
}
