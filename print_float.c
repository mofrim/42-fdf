/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:04:48 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 10:20:20 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Converts the floating point number INT_MIN <= d <= INT_MAX to a string.
 * Precision: 3 decimals.
 * WARNING: not suuper exact. F.ex. calling with 0.345 returns "0.344" :) */
char	*float_string(double d)
{
	char	*fstr;
	char	*itoa_str;
	int		i;

	fstr = malloc(15);
	i = 0;
	itoa_str = ft_itoa((int)d);
	ft_strlcpy(fstr, itoa_str, ft_strlen(itoa_str) + 1);
	free(itoa_str);
	if (d < 0)
		d *= -1;
	i += ft_strlen(fstr);
	fstr[i] = '.';
	d -= (int)d;
	d *= 10;
	fstr[++i] = (int)d + '0';
	d -= (int)d;
	d *= 10;
	fstr[++i] = (int)d + '0';
	d -= (int)d;
	d *= 10;
	fstr[++i] = (int)d + '0';
	fstr[++i] = 0;
	return (fstr);
}

void	print_mapinfo_float(t_myxvar *mx, const char *txt, double prop, int *i)
{
	char	*prop_str;
	char	*msg;

	prop_str = float_string(prop);
	msg = ft_strjoin(txt, prop_str);
	print_menu_text(mx, 15, 20 + (++(*i)) * 15, msg);
	free(msg);
	free(prop_str);
}
