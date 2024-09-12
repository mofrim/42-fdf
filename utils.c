/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:09:52 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 09:40:30 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_exit(void)
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}

void	free_split(char ***split)
{
	char **tmp;

	tmp = *split;
	while(**split)
	{
		free(**split);
		(*split)++;
	}
	free(tmp);
}

void print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			ft_printf("(%2d,%2d,%2d) ", map->vec_map[i][j].x, map->vec_map[i][j].y, map->vec_map[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
