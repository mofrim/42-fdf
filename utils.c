/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:09:52 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/25 23:24:08 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_exit(char *msg)
{
	if (msg)
		perror(msg);
	else
		perror("Error");
	exit(EXIT_FAILURE);
}

void	nullcheck(void *p, char *msg)
{
	if (!p)
		error_exit(msg);
}

void	free_split(char ***split)
{
	char	**tmp;

	tmp = *split;
	while (**split)
	{
		free(**split);
		(*split)++;
	}
	free(tmp);
}
