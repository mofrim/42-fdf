/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelcloud_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:35:04 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/19 11:20:45 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pxlcl_delone(t_pxlcloud *node)
{
	if (!node)
		return ;
	free(node->pixl);
	free(node);
}

void	pxcl_clear(t_pxlcloud **lst)
{
	t_pxlcloud	*tmp;

	if (!*lst)
		return ; while (*lst)
	{
		tmp = (*lst)->next;
		pxlcl_delone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_pxlcloud	*pxcl_new(t_pxl *pixl)
{
	t_pxlcloud *nn;

	nn = (t_pxlcloud *)malloc(sizeof(t_pxlcloud));
	if (!nn)
		return (NULL);
	nn->pixl = pixl ;
	nn->next = NULL;
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

// 2nd if: empty list given as NULL
// "always ensuring that newend->next == NULL"
// ...francinette does not like it. but it actually makes sense to me. still i
// will remove it. maybe it is better not to touch newend...
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
