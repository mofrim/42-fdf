/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:19:37 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/19 17:17:20 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pxlcloud *calc_circle_cloud(int x, int y, int radius)
{
	t_pxlcloud *pc;
	int			i;
	double		u;
	double		v;

	pc = pxlcl_new(x, y);
	i = 0;
	while (++i < radius)
	{
		u = x + i;
		v = sqrt(radius * radius - + 2 * radius * u);
		pxlcl_new(u, v);
		pxlcl_new(u, v);

	}



	return (pc);
}


void	draw_map_circles_size(int x, int y, t_myxvar mxv, int radius, char *colr)
{
	t_pxlcloud	*pxcl;
	t_pxlcloud	*pxcl_bak;

	pxcl = calc_circle_cloud(x, y, radius);
	pxcl_bak = pxcl;
	// print_linelst(linelst);
	while (pxcl)
	{
		mlx_pixel_put(mxv.mlx, mxv.win, pxcl->x, pxcl->y, rgb_to_int(colr));
		pxcl = pxcl->next;
	}
	pxlcl_clear(&pxcl_bak);
}


