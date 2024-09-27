/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:49:44 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 07:39:20 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_myxvar	*mxv;

	if (ac != 2)
	{
		ft_printf("Usage: ./fdf MAP_FILE\n");
		exit(0);
	}
	mxv = init_myxvar(av[1]);
	mlx_set_font(mxv->mlx, mxv->win, FONT);
	show_sidebar(mxv);
	draw_map_color_elev(mxv->cur_map, *mxv);
	mlx_key_hook(mxv->win, kbd_input_handler, mxv);
	mlx_loop(mxv->mlx);
}

// DEBUG
// 
// ft_printf("\n");
// print_map_without_offset(mxv->cur_map);
// ft_printf("\n");

// DEBUG test conversion
//
// ft_printf("\nint2rgb:\n");
// int rgb[3];
// int_to_rgb(rgb, rgb_to_int("ffffff"));
// ft_printf("int_to_rgb(rgb_to_int(010101)): %d %d %d\n",
// rgb[0], rgb[1], rgb[2]);
// ft_printf("rgb to int test: %d\n", rgb_to_int("ff"));

// DEBUG color line drawing test
//
// t_vec	a = {a.x = 0, a.y = 0, a.z = 0, a.colr = rgb_to_int("ff0000")};
// t_vec	b = {b.x = 100, b.y = 100, b.z = 0, b.colr = rgb_to_int("00ff00")};
// draw_color_line(a, b, *mxv);

// DEBUG disk drawing test
//
// t_pxl p = { p.x = 512, p.y = 384};
// draw_disk(p, 100, rgb_to_int("00ff00"), *mxv);

// DEBUG colormap
//
// mxv->colrmap = generate_colrmap(*mxv);
// int rgb[3];
// for (int i=0;i <= mxv->zdiff;i++) {
// 	int_to_rgb(rgb, mxv->colrmap[i]);
// 	ft_printf("int_to_rgb(colrmap): %d %d %d\n", rgb[0], rgb[1], rgb[2]);
// }
