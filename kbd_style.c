/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_style.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:58:10 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 15:39:15 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Set mapstyles with 1,2,3,4 keys. */
void	handle_mapstyle_keys(int key, t_myxvar *p)
{
	if (key == 49 || key == 50 || key == 51 || key == 52)
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
		if (key == 52)
		{
			p->mapstyle = 4;
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

/* Set markerstyle:
 * '0' = 48, markerstyle 1
 * '9' = 57, markerstyle 2
 */
void	handle_markerstyle_keys(int key, t_myxvar *mx)
{
	if (key == 48 || key == 57)
	{
		if (key == 48)
		{
			mx->markerstyle = 1;
			redraw_map(mx);
		}
		if (key == 57)
		{
			mx->markerstyle = 2;
			redraw_map(mx);
		}
	}
}
