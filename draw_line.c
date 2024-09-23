/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */

/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:17 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 10:01:45 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Draw line starting from vector a to vector b using mlx_pixel_put. */
void	draw_line(t_vec a, t_vec b, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int		N;
	int		i;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (fabs(dx) >= fabs(dy))
		N = fabs(dx);
	else
		N = fabs(dy);

	dx = dx / (double)N;
	dy = dy / (double)N;
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, a.x, a.y, rgb_to_int(colr));
		a.x += dx;
		a.y += dy;
		i++;
	}
}

// TODO maybe also adopt to new linedrawing style with vectors as args.
void	draw_line2(t_line line, char *colr, t_myxvar myxvar)
{
	double	dx;
	double	dy;
	int N;
	int i;

	dx = line.x1 - line.x0;
	dy = line.y1 - line.y0;
	if (fabs(dx) >= fabs(dy))
		N = fabs(dx);
	else
		N = fabs(dy);

	dx = dx / (double)N;
	dy = dy / (double)N;
	i = 0;
	while (i <= N)
	{
		mlx_pixel_put(myxvar.mlx, myxvar.win, line.x0, line.y0, rgb_to_int(colr));
		line.x0 += 2*dx;
		line.y0 += 2*dy;
		i += 2;
	}
}


// TODO maybe also adopt to new linedrawing style with vectors as args.
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
