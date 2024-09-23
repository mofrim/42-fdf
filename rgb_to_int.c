/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:07:24 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/23 10:08:34 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert a char to its int value. 0-9 -> 0-9, A -> 10, B-> 11, ..., F -> 15.
 */
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
 * Blue-value,... The left-most byte is all zeroes   */
int	rgb_to_int(char *rgbstr)
{
	int	red;
	int	green;
	int	blue;

	red = hexchar_to_int(rgbstr[1]) * 16 + hexchar_to_int(rgbstr[0]);
	green = hexchar_to_int(rgbstr[3]) * 16 + hexchar_to_int(rgbstr[2]);
	blue = hexchar_to_int(rgbstr[5]) * 16 + hexchar_to_int(rgbstr[4]);
	return (red << 16 | green << 8 | blue);
}
