/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:25 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/25 22:20:30 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft/libft.h"

t_vec	**get_map_from_fd(int fd, int rows, int cols);

int	get_map_rows(char *mapfile)
{
	int		rows;
	char	*line;
	int		fd;

	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		error_exit("could not open map file");
	rows = 0;
	line = get_next_line(fd);
	if (!line)
		error_exit("could not get line from map file");
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
		error_exit("could not open map file");
	cols = 0;
	line = get_next_line(fd);
	if (!line)
		error_exit(NULL);
	line_split = ft_split(line, ' ');
	free(line);
	if (!line_split)
		error_exit(NULL);
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
		error_exit(NULL);
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
		error_exit(NULL);
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
// double	*get_next_mapline(int fd, int cols)
// {
// 	char	*line;
// 	char	**line_split;
// 	double	*numline;
// 	int		i;
//
// 	line = get_next_line(fd);
// 	if (!line)
// 		error_exit();
// 	line_split = ft_split(line, ' ');
// 	free(line);
// 	if (!line_split)
// 		error_exit();
// 	numline = malloc(sizeof(double) * cols);
// 	i = -1;
// 	while (++i < cols)
// 	{
// 		if (!line_split[i])
// 		{
// 			ft_printf("Map error!\n");
// 			exit(1);
// 		}
// 		numline[i] = ft_atoi(line_split[i]);
// 	}
// 	free_split(&line_split);
// 	return (numline);
// }

double	*get_next_mapline(int fd, int cols)
{
	char	*line;
	char	**line_split;
	double	*numline;
	char	*colon;
	int		i;

	line = get_next_line(fd);
	if (!line)
		error_exit("could not get line from map file");
	line_split = ft_split(line, ' ');
	free(line);
	if (!line_split)
		error_exit("could not split line");
	numline = malloc(2 * sizeof(double) * cols);
	i = 0;
	while (i < cols)
	{
		if (!line_split[i])
		{
			ft_printf("Map error!\n");
			exit(1);
		}
		colon = ft_strchr(line_split[i], ',');
		if (colon)
		{
			numline[2 * i] = ft_atoi(line_split[i]);
			numline[2 * i + 1] = rgb_to_int(colon + 3);
		}
		else
		{
			numline[2 * i] = ft_atoi(line_split[i]);
			numline[2 * i + 1] = 16777215;
		}
		i++;
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
		error_exit("could not malloc map");
	i = -1;
	while (++i < rows)
	{
		map[i] = malloc(sizeof(t_vec) * cols);
		numline = get_next_mapline(fd, cols);
		if (!map[i])
			error_exit("could not malloc map row");
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
