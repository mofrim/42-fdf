/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */

/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:17 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/15 22:21:29 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Draw line starting from x to y using mlx_pixel_put. */
void	draw_line(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int N;
	int i;

	dx = fabs(line.x1 - line.x0);
	dy = fabs(line.y1 - line.y0);
	if (dx >= dy)
		N = dx;
	else
		N = dy;

	dx = dx / N;
	dy = dy / N;
	i = 0;
	while (i < N)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0, line.y0, rgb_to_int(colr));
		line.x0 += dx;
		line.y0 += dy;
		i++;
	}
}

/* Functioning version!!! Also being able to draw into negative xy-direction!!! */
void	draw_thick_line(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int N;
	int i;

	dx = (line.x1 - line.x0);
	dy = (line.y1 - line.y0);
	if (fabs(dx) >= fabs(dy))
		N = fabs(dx);
	else
		N = fabs(dy);
	dx = dx / (double)N;
	dy = dy / (double)N;
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 , line.y0, rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 - 1, line.y0, rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 + 1, line.y0, rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 , line.y0 - 1, rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 , line.y0 + 1, rgb_to_int(colr));
		line.x0 += dx;
		line.y0 += dy;
		i++;
	}
}
