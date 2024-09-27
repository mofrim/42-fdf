/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_mapline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:34:25 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 15:35:17 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Helper func for get_next_mapline. */
static void	parse_mapline(char **line_split, double *numline, int cols);

/* Get one map-row from file. */
double	*get_next_mapline(int fd, int cols)
{
	char	*line;
	char	**line_split;
	double	*numline;

	line = get_next_line(fd);
	nullcheck(line, "Could not get any line from map file");
	line_split = ft_split(line, ' ');
	free(line);
	nullcheck(line_split, "Could not split line");
	numline = malloc(2 * sizeof(double) * cols);
	nullcheck(numline, "Could not malloc numline");
	parse_mapline(line_split, numline, cols);
	free_split(&line_split);
	return (numline);
}

static void	parse_mapline(char **line_split, double *numline, int cols)
{
	char	*colon;
	int		i;

	i = -1;
	while (++i < cols)
	{
		if (!line_split[i])
		{
			ft_printf("Map error!\n");
			exit(1);
		}
		numline[2 * i] = ft_atoi(line_split[i]);
		colon = ft_strchr(line_split[i], ',');
		if (colon)
			numline[2 * i + 1] = rgb_to_int(colon + 3);
		else
			numline[2 * i + 1] = 16777215;
	}
}
