/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_style.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:58:10 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 11:58:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_mapstyle_keys(int key, t_myxvar *p)
{
	if (key == 49 || key == 50 || key == 51)
	{
		if (key == 49)
		{
			p->mapstyle = 1;
			redraw_map(p);
		}
		if (key == 50)
		{
			p->mapstyle = 2;
			redraw_map(p);
		}
		if (key == 51)
		{
			p->mapstyle = 3;
			redraw_map(p);
		}
	}
}

/* Marker size helper func. */
static void	change_marker_size(int key, t_myxvar *mx);

/* 'm' = 109, toggle show markers.
 * 'n' = 110, increase marker_size.
 * 'b' = 98,  decrease marker size.*/
void	handle_marker_keys(int key, t_myxvar *mx)
{
	if (key == 109 || key == 110 || key == 98)
	{
		if (key == 109)
		{
			if (mx->show_markers)
			{
				mx->show_markers = 0;
				redraw_map(mx);
			}
			else
			{
				mx->show_markers = 1;
				redraw_map(mx);
			}
		}
	}
	if (key == 110 || key == 98)
		change_marker_size(key, mx);
}

static void	change_marker_size(int key, t_myxvar *mx)
{
	if (key == 110 && mx->show_markers)
	{
		mx->marker_size++;
		redraw_map(mx);
	}
	if (key == 98 && mx->marker_size > 1 && mx->show_markers)
	{
		mx->marker_size--;
		redraw_map(mx);
	}
}
