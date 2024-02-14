/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:08:12 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/14 13:08:24 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int rotate(t_circular_double_link_list * cdl_list, char list_name, t_circular_double_link_list * ops)
{
    t_double_link_node * node;

    if (!(cdl_list && cdl_list->first_node))
        return (ERROR);
    if (list_name)
    {
        node = malloc(sizeof(*node));
        if (node && ops->pf_insert_end(ops, node))
            node->data = malloc(sizeof(char)*3);
        if (!node->data)
            return (ERROR);
        ((char *)node->data)[0] = 'r';
        ((char *)node->data)[1] = list_name;
        ((char *)node->data)[2] = '\0';
    }
    cdl_list->last_node = cdl_list->first_node;
    cdl_list->first_node = cdl_list->first_node->next;
    return (SUCCESS);
}

int rr(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b, t_circular_double_link_list * ops)
{
    t_double_link_node * node;
    rotate(cdll_a, 0, ops);
    rotate(cdll_b, 0, ops);

    node = malloc(sizeof(*node));
    if (node && ops->pf_insert_end(ops, node))
    {
        node->data = malloc(sizeof(char)*3); 
        if (!node->data)
            return (ERROR);
        node->data = (char *){"rr"};
    }
    else
        return (ERROR);
    return(SUCCESS);
}
