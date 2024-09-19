/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:19:37 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/19 11:40:30 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pxlcloud calc_circle_cloud(int x, int y)
{
	t_pxlcloud *pc;

	pc = pxlcl

	return (pc)
}


void	draw_map_circles_size(int x, int y, t_myxvar mxv, int size, char *colr)
{
	t_pxlcloud	*pxcl;
	t_pxlcloud	*pxcl_bak;

	pxcl = calc_circle_cloud(x, y);
	pxcl_bak = pxcl;
	// print_linelst(linelst);
	while (pxcl)
	{
		mlx_pixel_put(mxv.mlx, mxv.win, pxcl->pixl->x, pxcl->pixl->y, rgb_to_int(colr));
		pxcl = pxcl->next;
	}
	pxcl_clear(&pxcl_bak);
}


