/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_opti_rr1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:57:28 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 15:17:16 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	count_ops_rr(t_circular_db_ll *cdl_list, t_double_link_node **node,
		size_t *count, char ops)
{
	size_t	i;

	i = 0;
	while ((((char *)(*node)->data)[0] == 'r'
			&& ((char *)(*node)->data)[1] == 'r'
			&& ((char *)(*node)->data)[2] == ops
			&& (*node) != cdl_list->first_node) || i == 0)
	{
		if (((char *)(*node)->data)[0] == 'r'
			&& ((char *)(*node)->data)[1] == 'r'
			&& ((char *)(*node)->data)[2] == ops)
			++(*count);
		else
			break ;
		(*node) = (*node)->next;
		i = 1;
	}
}

void	insert_while_rrr(t_circular_db_ll *cdl_list,
		t_double_link_node *cdl_node, size_t *count_rr)
{
	while (*count_rr)
	{
		insert_rrr(cdl_list, cdl_node->previous);
		--(*count_rr);
	}
}

void	insert_rrr(t_circular_db_ll *cdl_list, t_double_link_node *node)
{
	t_double_link_node	*rr;

	if (cdl_list && cdl_list->first_node && node)
	{
		rr = malloc(sizeof(*rr));
		if (rr)
			rr->data = malloc(sizeof(char) * 4);
		if (rr->data)
		{
			((char *)(rr->data))[0] = 'r';
			((char *)(rr->data))[1] = 'r';
			((char *)(rr->data))[2] = 'r';
			((char *)(rr->data))[3] = '\0';
		}
		cdl_list->pf_insert_after(cdl_list, node, rr);
	}
}

void	iter_ops_rra(t_circular_db_ll *cdl_list,
		t_double_link_node **cdl_node_r, size_t *count_r,
		t_double_link_node **cdl_node)
{
	cdl_node_r[0] = *cdl_node;
	count_ops_rr(cdl_list, &cdl_node_r[0], &count_r[0], 'a');
	cdl_node_r[1] = cdl_node_r[0];
	count_ops_rr(cdl_list, &cdl_node_r[1], &count_r[1], 'b');
	*cdl_node = cdl_node_r[1];
}

void	iter_ops_rrb(t_circular_db_ll *cdl_list,
		t_double_link_node **cdl_node_r, size_t *count_r,
		t_double_link_node **cdl_node)
{
	cdl_node_r[1] = *cdl_node;
	count_ops_rr(cdl_list, &cdl_node_r[1], &count_r[0], 'b');
	cdl_node_r[0] = cdl_node_r[1];
	count_ops_rr(cdl_list, &cdl_node_r[0], &count_r[1], 'a');
	*cdl_node = cdl_node_r[0];
}
