/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:09:52 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/12 17:57:59 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_exit(void)
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}

void	free_split(char ***split)
{
	char **tmp;

	tmp = *split;
	while(**split)
	{
		free(**split);
		(*split)++;
	}
	free(tmp);
}
