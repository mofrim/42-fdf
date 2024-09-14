/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:25 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/14 09:16:30 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec	**get_map_from_fd(int fd, int rows, int cols);

int	get_map_rows(char *mapfile)
{
	int		rows;
	char	*line;
	int		fd;

	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		error_exit();
	rows = 0;
	line = get_next_line(fd);
	if (!line)
		error_exit();
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
int get_map_cols(char *mapfile)
{
	int		cols;
	char	*line;
	char	**line_split;
	int		fd;

	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		error_exit();
	cols = 0;
	line = get_next_line(fd);
	if (!line)
		error_exit();
	line_split = ft_split(line, ' ');
	free(line);
	if (!line_split)
		error_exit();
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

void	reset_map_fd(char *mapfile, int *fd)
{
	close(*fd);
	*fd = open(mapfile, O_RDONLY);
	if (*fd == -1)
		error_exit();
}

/* This func should read a map from file. It returns the map as a 2d-array of
 * integers for further processing. 
 *
 * Map is read as-is. After the map has been read there is a first resizing step
 * using winsize_x/y. But this is carried out elsewhere usin
 * initial_resize_map();
 */
t_map *read_map(char *mapfile)
{
	int		fd;
	int		rows;
	int		cols;
	t_map	*map;

	cols = get_map_cols(mapfile);
	rows = get_map_rows(mapfile);
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		error_exit();
	map = malloc(sizeof(t_map));
	ft_printf("found map with rows = %d, cols = %d\n", rows, cols);
	map->vec_map = get_map_from_fd(fd, rows, cols);
	map->cols = cols;
	map->rows = rows;
	close(fd);
	return (map);
}

/* OMG!!! so hard to handle these mallocs and frees correctly without completly
 * blowing up all the code. 
 * TODO make up something to make this memory safe. which is: free everything if
 * one malloc fails. */
double	*get_next_mapline(int fd, int cols)
{
	char	*line;
	char	**line_split;
	double	*numline;
	int		i;

	line = get_next_line(fd);
	if (!line)
		error_exit();
	line_split = ft_split(line, ' ');
	free(line);
	if (!line_split)
		error_exit();
	numline = malloc(sizeof(double) * cols);
	i = -1;
	while (++i < cols)
	{
		if (!line_split[i])
		{
			ft_printf("Map error!\n");
			exit(1);
		}
		numline[i] = ft_atoi(line_split[i]);
	}
	free_split(&line_split);
	return (numline);
}

t_vec	**get_map_from_fd(int fd, int rows, int cols)
{
	int	i;
	int	j;
	t_vec	**map;
	double	*numline;

	map = malloc(sizeof(t_vec *) * rows);
	if (!map)
		error_exit();
	i = -1;
	while (++i < rows)
	{
		map[i] = malloc(sizeof(t_vec) * cols);
		numline = get_next_mapline(fd, cols);
		if (!map[i])
			error_exit();
		j = 0;
		while (j < cols)
		{
			map[i][j].x = j;
			map[i][j].y = i;
			map[i][j].z = numline[j];
			ft_printf("map[%d][%d].z = %d\n", i, j, (int)map[i][j].z);
			j++;
		}
		free(numline);
	}
	return (map);
}
