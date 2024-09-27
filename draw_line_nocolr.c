/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_nocolr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:31:47 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 15:21:03 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Draw line starting from vector a to vector b using mlx_pixel_put. */
void	draw_line_nocolr(t_vec a, t_vec b, t_myxvar myxvar)
{
	double	dx;
	double	dy;
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
	i = 0;
	while (i <= n)
	{
		if (MAP_AREA_MINX <= a.x && a.x <= WINX && 0 <= a.y && a.y <= WINY)
			mlx_pixel_put(myxvar.mlx, myxvar.win, a.x, a.y, NOCOLR);
		a.x += dx;
		a.y += dy;
		i++;
	}
}

/* Put fat point on the screen. */
void	put_fat_pixel(int x, int y, t_myxvar mx, int colr)
{
	mlx_pixel_put(mx.mlx, mx.win, x, y, colr);
	mlx_pixel_put(mx.mlx, mx.win, x - 1, y, colr);
	mlx_pixel_put(mx.mlx, mx.win, x + 1, y, colr);
	mlx_pixel_put(mx.mlx, mx.win, x, y - 1, colr);
	mlx_pixel_put(mx.mlx, mx.win, x, y + 1, colr);
}

/* Draw thick line between vec a and b. */
void	draw_thick_line_nocolr(t_vec a, t_vec b, t_myxvar mx)
{
	double	dx;
	double	dy;
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
	i = 0;
	while (i <= n)
	{
		if (MAP_AREA_MINX <= a.x && a.x <= WINX && 0 <= a.y && a.y <= WINY)
			put_fat_pixel(a.x, a.y, mx, NOCOLR);
		a.x += dx;
		a.y += dy;
		i++;
	}
}
