/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:01:40 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 15:16:40 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	swap(t_circular_db_ll *cdl_list, char list_name, t_circular_db_ll *ops)
{
	t_double_link_node	*temp;
	t_double_link_node	*node;

	if (!(cdl_list && cdl_list->first_node && cdl_list->total >= 2))
		return (ERROR);
	if (list_name)
	{
		node = malloc(sizeof(*node));
		if (node && ops->pf_insert_end(ops, node))
			node->data = malloc(sizeof(char) * 3);
		if (!node->data)
			return (ERROR);
		((char *)node->data)[0] = 's';
		((char *)node->data)[1] = list_name;
		((char *)node->data)[2] = '\0';
	}
	temp = cdl_list->first_node;
	cdl_list->total--;
	cdl_list->first_node = temp->next;
	cdl_list->first_node->previous = cdl_list->last_node;
	cdl_list->last_node->next = cdl_list->first_node;
	cdl_list->pf_insert_after(cdl_list, cdl_list->first_node, temp);
	return (SUCCESS);
}

int	ss(t_circular_db_ll *cdll_a, t_circular_db_ll *cdll_b,
		t_circular_db_ll *ops)
{
	t_double_link_node	*node;

	swap(cdll_a, 0, ops);
	swap(cdll_b, 0, ops);
	node = malloc(sizeof(*node));
	if (node && ops->pf_insert_end(ops, node))
	{
		node->data = malloc(sizeof(char) * 3);
		if (!node->data)
			return (ERROR);
		node->data = (char *){"ss"};
	}
	else
		return (ERROR);
	return (SUCCESS);
}

void	write_push(t_double_link_node *node, char list_name)
{
	((char *)node->data)[0] = 'p';
	((char *)node->data)[1] = list_name;
	((char *)node->data)[2] = '\0';
}

void	push_switch_node(t_circular_db_ll *cdll_b, t_double_link_node *temp)
{
	if (cdll_b->total >= 2)
	{
		cdll_b->first_node = temp->next;
		cdll_b->first_node->previous = cdll_b->last_node;
		cdll_b->last_node->next = cdll_b->first_node;
	}
	else
	{
		cdll_b->first_node = NULL;
		cdll_b->last_node = NULL;
	}
}

int	push(t_circular_db_ll *cdll_a, t_circular_db_ll *cdll_b, char list_name,
		t_circular_db_ll *ops)
{
	t_double_link_node	*temp;
	t_double_link_node	*node;

	if (!(cdll_a && cdll_b && cdll_b->first_node))
		return (ERROR);
	if (list_name)
	{
		node = malloc(sizeof(*node));
		if (node && ops->pf_insert_end(ops, node))
			node->data = malloc(sizeof(char) * 3);
		if (!node->data)
			return (ERROR);
		write_push(node, list_name);
	}
	temp = cdll_b->first_node;
	push_switch_node(cdll_b, temp);
	cdll_b->total--;
	cdll_a->pf_insert_beginning(cdll_a, temp);
	return (SUCCESS);
}
