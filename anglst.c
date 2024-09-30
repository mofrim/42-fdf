/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anglst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 09:04:11 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/30 10:02:36 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	anglstclear(t_anglst **lst)
{
	t_anglst	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_anglst	*anglstnew(double a, double b, double g)
{
	t_anglst	*nn;

	nn = (t_anglst *)malloc(sizeof(t_anglst));
	if (!nn)
		return (NULL);
	nn->a = a;
	nn->b = b;
	nn->g = g;
	nn->next = NULL;
	return (nn);
}

// arg is again first element of list
t_anglst	*anglstlast(t_anglst *head)
{
	t_anglst	*cur;

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
void	anglst_add_back(t_anglst **head, t_anglst *newend)
{
	t_anglst	*oldlast;

	if (!newend)
		return ;
	if (!*head)
	{
		*head = newend;
		return ;
	}
	oldlast = anglstlast(*head);
	oldlast->next = newend;
}

void	print_anglst(t_anglst *head)
{
	t_anglst	*p;
	char		*a;
	char		*b;
	char		*g;

	p = head;
	while (p)
	{
		a = float_string(p->a);
		b = float_string(p->b);
		g = float_string(p->g);
		ft_printf("(a,b,g) = (%s,%s,%s)\n", a, b, g);
		free(a);
		free(b);
		free(g);
		p = p->next;
	}
}
