/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all_the_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:30:11 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/19 20:04:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	*make_line(t_vec a, t_vec b)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	line->x0 = a.x;
	line->y0 = a.y;
	line->x1 = b.x;
	line->y1 = b.y;
	return (line);
}

t_linelst	*generate_linelst(t_map *map)
{
	t_linelst	*ll;
	t_line		*line;
	t_vec		**vmap;
	int			i;
	int			j;

	vmap = map->vec_map;
	ll = NULL;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{

			/* first line. */
			if (i == 0 && j == 0)
			{
				line = make_line(vmap[0][0], vmap[1][0]);
				linelst_add_back(&ll, linelstnew(line));
				line = make_line(vmap[0][0], vmap[0][1]);
				linelst_add_back(&ll, linelstnew(line));
			}
			else if (i == 0 && 0 < j && j < map->cols - 1)
			{
				line = make_line(vmap[0][j], vmap[1][j]);
				linelst_add_back(&ll, linelstnew(line));
				line = make_line(vmap[0][j], vmap[0][j + 1]);
				linelst_add_back(&ll, linelstnew(line));
			}
			else if (i == 0 && j == map->cols - 1)
			{
				line = make_line(vmap[0][j], vmap[1][j]);
				linelst_add_back(&ll, linelstnew(line));
			}

			/* in between. */
			if (i != 0 && i < map->rows - 1 && j == 0)
			{
				line = make_line(vmap[i][j], vmap[i][j + 1]);
				linelst_add_back(&ll, linelstnew(line));
				line = make_line(vmap[i][j], vmap[i + 1][j]);
				linelst_add_back(&ll, linelstnew(line));
			}
			else if (i != 0 && i < map->rows - 1 && 0 < j && j < map->cols - 1)
			{
				line = make_line(vmap[i][j], vmap[i][j + 1]);
				linelst_add_back(&ll, linelstnew(line));
				line = make_line(vmap[i][j], vmap[i + 1][j]);
				linelst_add_back(&ll, linelstnew(line));
			}
			else if (i != 0 && i < map->rows - 1 && j == map->cols - 1)
			{
				line = make_line(vmap[i][j], vmap[i + 1][j]);
				linelst_add_back(&ll, linelstnew(line));
			}

			/* last line. */
			if (i == map->rows - 1 && j == 0)
			{
				line = make_line(vmap[i][j], vmap[i][j + 1]);
				linelst_add_back(&ll, linelstnew(line));
			}
			else if (i == map->rows - 1 && 0 < j && j < map->cols - 1)
			{
				line = make_line(vmap[i][j], vmap[i][j + 1]);
				linelst_add_back(&ll, linelstnew(line));
			}
		}
	}
	return (ll);
}

void	print_linelst(t_linelst *ll)
{
	ft_printf("\nPrinting linelst:\n");
	while(ll)
	{
		ft_printf("(%d, %d) -> (%d, %d)\n", (int)ll->line->x0, (int)ll->line->y0, (int)ll->line->x1, (int)ll->line->y1);
		ll = ll->next;
	}
}

/* For every point on the map find all the neighbors the will have to be drawn
 * to. */
void	draw_all_the_lines(t_map *map, t_myxvar myxvar)
{
	t_linelst	*linelst;
	t_linelst	*ll_bak;

	linelst = generate_linelst(map);
	ll_bak = linelst;

	// DEBUG
	// print_map(map);
	// print_linelst(linelst);

	while (linelst)
	{
		draw_thick_line(*linelst->line, WHITE2, myxvar);
		linelst = linelst->next;
	}
	linelstclear(&ll_bak);
}
