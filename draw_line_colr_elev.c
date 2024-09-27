/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_colr_elev.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:06:15 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 15:00:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Get the pixel color from colormap stored in my xvar. */
int	get_elev_colr(int z, t_myxvar mxv)
{
	return (mxv.colrmap[(int)(z / mxv.zfac) - mxv.zmin]);
}

/* Draw a colored line using the z-values (wich have been reset to orig_map's)
 * and the colormap calculating on the initial z-values. */
void	draw_line_colr_elev(t_vec a, t_vec b, t_myxvar mxv)
{
	double	dx;
	double	dy;
	double	dz;
	int		n;
	int		i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (fabs(dx) >= fabs(dy))
		n = fabs(dx);
	else
		n = fabs(dy);
	dx = dx / (double)n;
	dy = dy / (double)n;
	dz = (b.z - a.z) / (double)n;
	i = 0;
	while (i <= n)
	{
		if (MAP_AREA_MINX <= a.x && a.x <= WINX && 0 <= a.y && a.y <= WINY)
			mlx_pixel_put(mxv.mlx, mxv.win, a.x, a.y, get_elev_colr(a.z, mxv));
		a.x += dx;
		a.y += dy;
		a.z += dz;
		i++;
	}
}

/* Draw a colored line using the z-values (wich have been reset to orig_map's)
 * and the colormap calculating on the initial z-values. */
void	draw_fat_line_colr_elev(t_vec a, t_vec b, t_myxvar mx)
{
	double	dx;
	double	dy;
	double	dz;
	int		n;
	int		i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (fabs(dx) >= fabs(dy))
		n = fabs(dx);
	else
		n = fabs(dy);
	dx = dx / (double)n;
	dy = dy / (double)n;
	dz = (b.z - a.z) / (double)n;
	i = 0;
	while (i <= n)
	{
		if (MAP_AREA_MINX <= a.x && a.x <= WINX && 0 <= a.y && a.y <= WINY)
			put_fat_pixel(a.x, a.y, mx, get_elev_colr(a.z, mx));
		a.x += dx;
		a.y += dy;
		a.z += dz;
		i++;
	}
}
