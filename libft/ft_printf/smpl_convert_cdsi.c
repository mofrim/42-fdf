/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smpl_convert_cdsi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:16 by fmaurer           #+#    #+#             */
/*   Updated: 2024/08/05 19:35:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Print smpl 'i' conversion. */
int	ftpr_converter_i(int i)
{
	char	*num;
	int		r;

	num = ft_itoa(i);
	ft_putstr(num);
	r = ft_strlen(num);
	free(num);
	return (r);
}

/* Print smpl 'd' conversion. */
int	ftpr_converter_d(int i)
{
	char	*num;
	int		r;

	num = ft_itoa(i);
	ft_putstr(num);
	r = ft_strlen(num);
	free(num);
	return (r);
}

/* Print smpl 'u' conversion. */
int	ftpr_converter_u(unsigned int i)
{
	char	*num;
	int		r;

	num = ftpr_utoa(i);
	ft_putstr(num);
	r = ft_strlen(num);
	free(num);
	return (r);
}

/* Print smpl 'c' conversion. */
int	ftpr_converter_c(int i)
{
	ft_putchar_fd(i, 1);
	return (1);
}

/* Print smpl 's' conversion. */
int	ftpr_converter_s(char *str)
{
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	ft_putstr(str);
	return (ft_strlen(str));
}
