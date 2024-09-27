/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:07:24 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/27 10:46:58 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Convert a char to its int value. 0-9 -> 0-9, A/a -> 10, B/b-> 11, ..., F/f
 * -> 15. */
int	hexchar_to_int(char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	if ('a' <= c && c <= 'f' )
		return (c - 87);
	if ('A' <= c && c <= 'F' )
		return (c - 55);
	return (-1);
}

/* Converts a RGB string given as parameter f.ex. like "RRGGBB" to an integer
 * where the least siginifcant byte (the right most 8 bits) represents the
 * Blue-value,... The left-most byte is all zeroes.
 *
 * What to do with "0xff"? I would say this is supposed to be 0xff0000,
 * similarly 0x00ff is 0x00ff00. so...*/
int	rgb_to_int(char *rgbstr)
{
	int	red;
	int	green;
	int	blue;

	if (!ft_strlen(rgbstr) || ft_strlen(rgbstr) % 2)
		return (0);
	if (ft_strlen(rgbstr) == 2)
	{
		red = hexchar_to_int(rgbstr[0]) * 16 + hexchar_to_int(rgbstr[1]);
		return (red << 16);
	}
	if (ft_strlen(rgbstr) == 4)
	{
		red = hexchar_to_int(rgbstr[0]) * 16 + hexchar_to_int(rgbstr[1]);
		green = hexchar_to_int(rgbstr[2]) * 16 + hexchar_to_int(rgbstr[3]);
		return (red << 16 | green << 8);
	}
	red = hexchar_to_int(rgbstr[0]) * 16 + hexchar_to_int(rgbstr[1]);
	green = hexchar_to_int(rgbstr[2]) * 16 + hexchar_to_int(rgbstr[3]);
	blue = hexchar_to_int(rgbstr[4]) * 16 + hexchar_to_int(rgbstr[5]);
	return (red << 16 | green << 8 | blue);
}

/* Inverse conversion from a given rgb-integer value to byte values stored in an
 * int[3] array using in-place array assignement in order to avoid malloc
 * hassle. */
void	int_to_rgb(int rgb_arr[3], int rgb_num)
{
	rgb_arr[0] = (rgb_num >> 16) & 255;
	rgb_arr[1] = (rgb_num >> 8) & 255;
	rgb_arr[2] = rgb_num & 255;
}
