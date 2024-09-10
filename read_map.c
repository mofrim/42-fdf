/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:35:25 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/09 23:26:55 by fmaurer          ###   ########.fr       */
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
	if (!line_split)
		error_exit();
	while (line_split[cols])
		cols++;
	free_split(&line_split);
	free(line);
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
 */
t_map *read_map(char *mapfile)
{
	int		fd;
	int		rows;
	int		cols;
	t_map	*map;

	rows = get_map_rows(mapfile);
	cols = get_map_cols(mapfile);
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		error_exit();
	map = malloc(sizeof(t_map));
	map->vec_map = get_map_from_fd(fd, rows, cols);
	map->cols = cols;
	map->rows = rows;
	ft_printf("rows = %d, cols = %d\n", rows, cols);
	return (map);
}

/* OMG!!! so hard to handle these mallocs and frees correctly without completly
 * blowing up all the code. 
 * TODO make up something to make this memory safe. which is: free everything if
 * one malloc fails. */
int	*get_next_mapline(int fd, int cols)
{
	char	*line;
	char	**line_split;
	int		*intline;
	int		i;

	line = get_next_line(fd);
	if (!line)
		error_exit();
	line_split = ft_split(line, ' ');
	if (!line_split)
		error_exit();
	intline = malloc(sizeof(int) * cols);
	i = -1;
	while (++i < cols)
	{
		if (!line_split[i])
		{
			ft_printf("Map error!\n");
			exit(1);
		}
		intline[i] = ft_atoi(line_split[i]);
	}
	return (intline);
}

t_vec	**get_map_from_fd(int fd, int rows, int cols)
{
	int	i;
	int	j;
	t_vec	**map;
	int		*intline;

	map = malloc(sizeof(t_vec *) * rows);
	if (!map)
		error_exit();
	i = -1;
	while (++i < rows)
	{
		map[i] = malloc(sizeof(t_vec) * cols);
		intline = get_next_mapline(fd, cols);
		if (!map[i])
			error_exit();
		j = 0;
		while (j < cols)
		{
			map[i][j].x = j;
			map[i][j].y = rows - i - 1;
			map[i][j].z = intline[j];
			j++;
		}
		free(intline);
	}
	return (map);
}




// int **read_map(char *mapfile)
// {
// 	int		fd;
// 	char	*line;
// 	char	**line_split;
// 	int		i;
// 	int		rows;
// 	int		cols;
// 	int		**map;
//
// 	fd = open(mapfile, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error");
// 		exit(EXIT_FAILURE);
// 	}
//
// 	line = get_next_line(fd);
// 	line_split = NULL;
// 	rows = 0;
// 	cols = 0;
// 	while (line)
// 	{
// 		// ft_printf("sine: %s", line);
// 		rows++;
// 		line_split = ft_split(line, ' ');
// 		i = -1;
// 		while (line_split[++i])
// 		{
// 			ft_printf("%3s", line_split[i]);
// 			if (!ft_strrchr(line_split[i], '\n'))
// 				ft_printf(",");
// 		}
// 		cols = i;
// 		if (line_split)
// 			free_split(&line_split);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	map = malloc(rows * sizeof(int *));
//
// 	ft_printf("rows = %d, cols = %d\n", rows, cols);
// 	return (NULL);
// }
