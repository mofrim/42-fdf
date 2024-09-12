/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:09:52 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 11:30:41 by fmaurer          ###   ########.fr       */
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

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
			ft_printf("(%2d,%2d,%2d) ", (int)map->vec_map[i][j].x, (int)map->vec_map[i][j].y, (int)map->vec_map[i][j].z);
		ft_printf("\n");
	}
}
