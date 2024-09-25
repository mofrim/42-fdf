/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:25 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/25 23:56:43 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

static int		get_map_cols(char *mapfile);
static int		get_map_rows(char *mapfile);
static t_vec	**get_map_from_fd(int fd, int rows, int cols);

/* This func should read a map from file. It returns the map as a 2d-array of
 * integers for further processing.
 *
 * Map is read as-is. After the map has been read there is a first resizing step
 * using winsize_x/y. But this is carried out elsewhere usin
 * initial_resize_map();
 */
t_map	*read_map(char *mapfile)
{
	int		fd;
	int		rows;
	int		cols;
	t_map	*map;

	cols = get_map_cols(mapfile);
	rows = get_map_rows(mapfile);
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		error_exit(NULL);
	map = malloc(sizeof(t_map));
	ft_printf("Found map with rows = %d, cols = %d\n", rows, cols);
	map->vec_map = get_map_from_fd(fd, rows, cols);
	map->cols = cols;
	map->rows = rows;
	close(fd);
	return (map);
}

static int	get_map_rows(char *mapfile)
{
	int		rows;
	char	*line;
	int		fd;

	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		error_exit("Could not open map file");
	rows = 0;
	line = get_next_line(fd);
	nullcheck(line, "Could not get rows from mapfile or empty file");
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rows);
}

/* Had to continue reading till EOF, otherwise the next get_next_line would read
 * the 2nd line!!! Brainfuck. So the opening and closing of fd has no effect on
 * gnl in this case. lseek() woud be nice to have... */
static int	get_map_cols(char *mapfile)
{
	int		cols;
	char	*line;
	char	**line_split;
	int		fd;

	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		error_exit("Could not open mapfile");
	cols = 0;
	line = get_next_line(fd);
	nullcheck(line, "Could not get cols from mapfile or empty file");
	line_split = ft_split(line, ' ');
	free(line);
	nullcheck(line_split, NULL);
	while (line_split[cols])
		cols++;
	while (line)
	{
		line = get_next_line(fd);
		free(line);
	}
	free_split(&line_split);
	close(fd);
	return (cols);
}

static t_vec	**get_map_from_fd(int fd, int rows, int cols)
{
	int		i;
	int		j;
	t_vec	**map;
	double	*numline;

	map = malloc(sizeof(t_vec *) * rows);
	nullcheck(map, "Could not malloc map");
	i = -1;
	while (++i < rows)
	{
		map[i] = malloc(sizeof(t_vec) * cols);
		numline = get_next_mapline(fd, cols);
		nullcheck(map[i], "Could not malloc map row");
		j = 0;
		while (j < cols)
		{
			map[i][j].x = j;
			map[i][j].y = i;
			map[i][j].z = numline[2 * j];
			map[i][j].colr = numline[2 * j + 1];
			j++;
		}
		free(numline);
	}
	return (map);
}
