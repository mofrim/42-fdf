/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelcloud_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:35:04 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/19 17:08:38 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pxlcl_delone(t_pxlcloud *node)
{
	if (!node)
		return ;
	free(node);
}

void	pxcl_clear(t_pxlcloud **lst)
{
	t_pxlcloud	*tmp;

	if (!*lst)
		return ; 
	while (*lst)
	{
		tmp = (*lst)->next;
		pxlcl_delone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_pxlcloud	*pxcl_new(double x, double y)
{
	t_pxlcloud *nn;

	nn = (t_pxlcloud *)malloc(sizeof(t_pxlcloud));
	if (!nn)
		return (NULL);
	nn->x = x;
	nn->y = y;
	return (nn);
}

// arg is again first element of list
t_pxlcloud *pxcl_last(t_pxlcloud *head)
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
	t_pxlcloud *oldlast;

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
