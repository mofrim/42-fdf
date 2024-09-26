/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_nocolr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:31:47 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/26 16:54:58 by fmaurer          ###   ########.fr       */
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
		mlx_pixel_put(myxvar.mlx, myxvar.win, a.x, a.y, NOCOLR);
		a.x += dx;
		a.y += dy;
		i++;
	}
}

void	draw_thick_line_nocolr(t_vec a, t_vec b, t_myxvar myxvar)
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
		mlx_pixel_put(myxvar.mlx, myxvar.win, a.x, a.y, NOCOLR);
		mlx_pixel_put(myxvar.mlx, myxvar.win, a.x - 1, a.y, NOCOLR);
		mlx_pixel_put(myxvar.mlx, myxvar.win, a.x + 1, a.y, NOCOLR);
		mlx_pixel_put(myxvar.mlx, myxvar.win, a.x, a.y - 1, NOCOLR);
		mlx_pixel_put(myxvar.mlx, myxvar.win, a.x, a.y + 1, NOCOLR);
		a.x += dx;
		a.y += dy;
		i++;
	}
}
