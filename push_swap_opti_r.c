/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_opti_r.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:56:11 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 13:12:02 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void insert_while_rr(t_circular_db_ll * cdl_list, t_double_link_node * cdl_node, size_t * count_rr)
{
    while (*count_rr)
    {
        insert_rr(cdl_list, cdl_node->previous);
        --(*count_rr);
    }
}

void process_ops_r(t_circular_db_ll * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node)
{
    count_r[1] = 0;
    count_r[0] = 0;
    if (((char*)(*cdl_node)->data)[0] == 'r' && ((char*)(*cdl_node)->data)[1] == 'a')
        iter_ops_ra(cdl_list, cdl_node_r, count_r, cdl_node);
    else if (((char*)(*cdl_node)->data)[0] == 'r' && ((char*)(*cdl_node)->data)[1] == 'b')
        iter_ops_rb(cdl_list, cdl_node_r, count_r, cdl_node);
    else
        *cdl_node = (*cdl_node)->next;
}

int optimize_ops_r(t_circular_db_ll * cdl_list)
{
    t_double_link_node ** cdl_node_r;
    t_double_link_node * cdl_node;
    size_t * count_r;
    size_t count_rr;

    count_rr = 0;
    cdl_node_r = malloc(sizeof(cdl_node_r)*2);
    count_r = malloc(sizeof(count_r)*2);
    if (!(cdl_list && cdl_list->first_node))
        return(free(cdl_node_r), free(count_r), ERROR);
    cdl_node = cdl_list->first_node;
    do {
        process_ops_r(cdl_list, cdl_node_r, count_r, &cdl_node);
        if (count_r[0] && count_r[1])
        {
            del_r(cdl_list, cdl_node_r, count_r, &count_rr);
            insert_while_rr(cdl_list, cdl_node, &count_rr); 
        }
    } while (cdl_node != cdl_list->first_node);
    return(free(cdl_node_r), free(count_r), SUCCESS);
}
