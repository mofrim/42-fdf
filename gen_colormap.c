/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_colormap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:04:24 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 15:34:09 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Generate a simple colormap of the following structure:
 *
 * 0 -> diff/2 gen colrs between 0000ff and 00ff00 
 * diff/2 -> diff gen colrs between 00ff00 and ff0000
 */
int	*generate_colrmap(t_myxvar mxv)
{
	int	*cmap;
	int	i;
	int	n;

	cmap = malloc(sizeof(int) * (mxv.zdiff + 1));
	if (mxv.zdiff == 0)
	{
		cmap[0] = rgb_to_int("aaaaaa");
		return (cmap);
	}
	i = -1;
	n = mxv.zdiff / 2;
	while (++i <= n)
		cmap[i] = (((int)(255 * (double)i / n)) << 8) | ((int)(255 * (1.0 - \
						(double)i / n)));
	i = -1;
	while (++i + n + 1 <= mxv.zdiff)
		cmap[n + 1 + i] = (((int)(255 * (double)i / n)) << 16) | (((int)(255 * \
						(1.0 - (double)i / n))) << 8);
	return (cmap);
}
