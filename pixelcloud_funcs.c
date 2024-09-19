/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelcloud_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:35:04 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/19 20:35:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pxcl_clear(t_pxlcloud **p)
{
	t_pxlcloud	*tmp;

	if (!*p)
		return ;
	while (*p)
	{
		tmp = (*p)->next;
		if (*p)
			free(*p);
		*p = tmp;
	}
	*p = NULL;
}

t_pxlcloud	*pxcl_new(double x, double y)
{
	t_pxlcloud	*nn;

	nn = (t_pxlcloud *)malloc(sizeof(t_pxlcloud));
	if (!nn)
		return (NULL);
	nn->x = x;
	nn->y = y;
	nn->next = NULL;
	return (nn);
}

// arg is again first element of list
t_pxlcloud	*pxcl_last(t_pxlcloud *head)
{
	t_pxlcloud	*cur;

	if (head == NULL)
		return (NULL);
	cur = head;
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	pxcl_add_back(t_pxlcloud **head, t_pxlcloud *newend)
{
	t_pxlcloud	*oldlast;

	if (!newend)
		return ;
	if (!*head)
	{
		*head = newend;
		return ;
	}
	oldlast = pxcl_last(*head);
	oldlast->next = newend;
}

void	pxcl_print_size(t_pxlcloud *p)
{
	int	i;

	i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	ft_printf("pixelcloud size: %d\n", i);
}
