/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:33:41 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 07:08:41 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/* mat * vec. works in-place. */
void	mult_mat_vec(double a[3][3], t_vec *v)
{
	v->x = (int)((double)v->x * a[0][0] + (double)v->y * a[0][1] + (double)v->z * a[0][2]);
	v->y = (int)((double)v->x * a[1][0] + (double)v->y * a[1][1] + (double)v->z * a[1][2]);
	v->z = (int)((double)v->x * a[2][0] + (double)v->y * a[2][1] + (double)v->z * a[2][2]);
}

void	mult_mat_map(double a[3][3], t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
			mult_mat_vec(a, &map->vec_map[i][j]);
	}
}

void mult_mat_by_scalar(double (*a)[3][3], double scalar)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			(*a)[i][j] *= scalar;
	}
}

// FIXME remove me before submission!!!!
void	print_mat(double a[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
			printf("%.2lf ", a[i][j]);
		printf("\n");
	}
}
