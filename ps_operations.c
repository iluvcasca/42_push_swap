/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:01:40 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/11 10:33:42 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int swap(t_circular_double_link_list * cdl_list, char list_name)
{
    t_double_link_node * temp;
    if (!(cdl_list && cdl_list->first_node && cdl_list->total >= 2))
        return (ERROR);
    temp = cdl_list->first_node; 
    cdl_list->total--;
    cdl_list->first_node = temp->next;
    cdl_list->first_node->previous = cdl_list->last_node;
    cdl_list->last_node->next = cdl_list->first_node;
    cdl_list->pf_insert_after(cdl_list, cdl_list->first_node, temp);
    if (list_name)
        ft_printf("s%c\n", list_name);
    return (SUCCESS);
}

void ss(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b)
{
    swap(cdll_a, 0);
    swap(cdll_b, 0);
    ft_printf("ss\n");
}

int push(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b, char list_name)
{
    t_double_link_node * temp;

    if (!(cdll_a && cdll_b && cdll_b->first_node))
        return (ERROR);
    temp = cdll_b->first_node;
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
    cdll_b->total--;
    cdll_a->pf_insert_beginning(cdll_a, temp);
    if (list_name)
        ft_printf("p%c\n", list_name);
    return (SUCCESS);
}

int rotate(t_circular_double_link_list * cdl_list, char list_name)
{
    if (!(cdl_list && cdl_list->first_node))
        return (ERROR);
    cdl_list->last_node = cdl_list->first_node;
    cdl_list->first_node = cdl_list->first_node->next;
    if (list_name)
        ft_printf("r%c\n", list_name);
    return (SUCCESS);
}

void rr(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b)
{
    rotate(cdll_a, 0);
    rotate(cdll_b, 0);
    ft_printf("rr\n");
}
