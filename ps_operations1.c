/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:14:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/13 10:35:45 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int r_rotate(t_circular_double_link_list * cdl_list, char list_name, t_circular_double_link_list * ops)
{
    t_double_link_node * node;
    if (!(cdl_list && cdl_list->first_node))
        return (ERROR);
    if (list_name)
    {
        node = malloc(sizeof(*node));
        if (node && ops->pf_insert_end(ops, node))
            node->data = malloc(sizeof(char)*4);
        if (!node->data)
            return (ERROR);
        ((char *)node->data)[0] = 'r';
        ((char *)node->data)[1] = 'r';
        ((char *)node->data)[2] = list_name;
        ((char *)node->data)[3] = '\0';
    }
    cdl_list->first_node = cdl_list->last_node;
    cdl_list->last_node = cdl_list->last_node->previous;
    return (SUCCESS);
}

int r_rr(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b, t_circular_double_link_list * ops)
{
    t_double_link_node * node;

    r_rotate(cdll_a, 0, ops);
    r_rotate(cdll_b, 0, ops);

    node = malloc(sizeof(*node));
    if (node && ops->pf_insert_end(ops, node))
    {
        node->data = malloc(sizeof(char)*4); 
        if (!node->data)
            return (ERROR);
        node->data = (char *){"rrr"};
    }
    else
        return (ERROR);
    return(SUCCESS);
}

void r_rotate_n(t_circular_double_link_list * cdl_list, char list_name, size_t n, t_circular_double_link_list * ops)
{
    size_t i;

    i = 0;
    while(i < n)
    {
        r_rotate(cdl_list, list_name, ops);
        ++i;
    }
}

void rotate_n(t_circular_double_link_list * cdl_list, char list_name, size_t n, t_circular_double_link_list * ops)
{
    size_t i;

    i = 0;
    while(i < n)
    {
        rotate(cdl_list, list_name, ops);
        ++i;
    }
}

void push_n(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b, char list_name, size_t n, t_circular_double_link_list * ops)
{
    size_t i;

    i = 0;
    while(i < n)
    {
        push(cdll_a, cdll_b, list_name, ops);
        ++i;
    }
}
