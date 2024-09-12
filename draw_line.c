/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */

/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:17 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 10:16:26 by fmaurer          ###   ########.fr       */
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

	dx = fabs((double)line.x1 - (double)line.x0);
	dy = fabs((double)line.y1 - (double)line.y0);
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

/* Draw line starting from x to y using mlx_pixel_put. */
void	draw_thick_line(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int N;
	int i;

	dx = fabs((double)line.x1 - (double)line.x0);
	dy = fabs((double)line.y1 - (double)line.y0);
	if (dx >= dy)
		N = dx;
	else
		N = dy;
	dx = dx / N;
	dy = dy / N;
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 + (int)(dx * i), line.y0 + (int)(dy * i), rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 + (int)(dx * i-1), line.y0 + (int)(dy * i), rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 + (int)(dx * i+1), line.y0 + (int)(dy * i), rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 + (int)(dx * i), line.y0 + (int)(dy * i-1), rgb_to_int(colr));
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0 + (int)(dx * i), line.y0 + (int)(dy * i+1), rgb_to_int(colr));
		// line.x0 += dx;
		// line.y0 += dy;
		i++;
	}
	// ft_printf("x1, y1 = %d, %d \t x0+dx, y0+dy = %d, %d\n", line.x1, line.y1, line.x0 + (int)dx * (i-1), line.y0 + (int)(dy * (i-1)));
}
