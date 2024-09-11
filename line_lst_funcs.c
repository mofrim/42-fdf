/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_lst_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:35:04 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/11 20:20:17 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	linelstdelone(t_linelst *node)
{
	if (!node)
		return ;
	free(node->line);
	free(node);
}

void	linelstclear(t_linelst **lst)
{
	t_linelst	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		linelstdelone(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_linelst	*linelstnew(t_line *line)
{
	t_linelst	*nn;

	nn = (t_linelst *)malloc(sizeof(t_linelst));
	if (!nn)
		return (NULL);
	nn->line = line ;
	nn->next = NULL;
	return (nn);
}

// arg is again first element of list
t_linelst	*linelstlast(t_linelst *head)
{
	t_linelst	*cur;

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
void	linelst_add_back(t_linelst **head, t_linelst *newend)
{
	t_linelst	*oldlast;

	if (!newend)
		return ;
	if (!*head)
	{
		*head = newend;
		return ;
	}
	oldlast = linelstlast(*head);
	oldlast->next = newend;
}
