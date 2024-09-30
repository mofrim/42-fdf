/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_btn_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:23:54 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 10:09:35 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Cleanly exit the program when close button is clicked. */
int	close_btn_handler(t_myxvar *mx)
{
	ft_printf("Close button clicked. Exiting.\n");
	mlx_destroy_window(mx->mlx, mx->win);
	if (mx->orig_map == mx->cur_map)
	{
		free_map(&mx->orig_map);
		mx->cur_map = NULL;
	}
	else
		free_map(&mx->orig_map);
	if (mx->cur_map)
		free_map(&mx->cur_map);
	free(mx->colrmap);
	anglstclear(&mx->anglst);
	mlx_destroy_display(mx->mlx);
	free(mx->mlx);
	free(mx);
	exit(0);
}
