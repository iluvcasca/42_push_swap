/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_opti_rr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:37:03 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 15:17:24 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	process_ops_rr(t_circular_db_ll *cdl_list,
		t_double_link_node **cdl_node_r, size_t *count_r,
		t_double_link_node **cdl_node)
{
	count_r[1] = 0;
	count_r[0] = 0;
	if (((char *)(*cdl_node)->data)[0] == 'r'
		&& ((char *)(*cdl_node)->data)[1] == 'r'
		&& ((char *)(*cdl_node)->data)[2] == 'a')
		iter_ops_rra(cdl_list, cdl_node_r, count_r, cdl_node);
	else if (((char *)(*cdl_node)->data)[0] == 'r'
		&& ((char *)(*cdl_node)->data)[1] == 'r'
		&& ((char *)(*cdl_node)->data)[2] == 'b')
		iter_ops_rrb(cdl_list, cdl_node_r, count_r, cdl_node);
	else
		*cdl_node = (*cdl_node)->next;
}

int	optimize_ops_rr(t_circular_db_ll *cdl_list)
{
	t_double_link_node	**cdl_node_r;
	t_double_link_node	*cdl_node;
	size_t				*count_r;
	size_t				count_rr[2];

	count_rr[0] = 0;
	count_rr[1] = 0;
	cdl_node_r = malloc(sizeof(cdl_node_r) * 2);
	count_r = malloc(sizeof(count_r) * 2);
	if (!(cdl_list && cdl_list->first_node))
		return (free(cdl_node_r), free(count_r), ERROR);
	cdl_node = cdl_list->first_node;
	while (cdl_node != cdl_list->first_node || count_rr[1] == 0)
	{
		process_ops_rr(cdl_list, cdl_node_r, count_r, &cdl_node);
		if (count_r[0] && count_r[1])
		{
			del_r(cdl_list, cdl_node_r, count_r, &count_rr[0]);
			insert_while_rrr(cdl_list, cdl_node, &count_rr[0]);
		}
		count_rr[1] = 1;
	}
	return (free(cdl_node_r), free(count_r), SUCCESS);
}
