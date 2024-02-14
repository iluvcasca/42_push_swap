/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_opti_r1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:56:28 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/14 12:56:39 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
void count_ops_r(t_circular_double_link_list * cdl_list, t_double_link_node ** node, size_t * count, char ops)
{
    do
    {
        if (((char *)(*node)->data)[0] == 'r' && ((char *)(*node)->data)[1] == ops)
            ++(*count);
        else
            break;
        (*node) = (*node)->next;
    }
    while (((char *)(*node)->data)[0] == 'r' && ((char *)(*node)->data)[1] == ops && (*node) != cdl_list->first_node);
}

void insert_rr(t_circular_double_link_list * cdl_list, t_double_link_node * node)
{
    t_double_link_node * rr;

    if (cdl_list && cdl_list->first_node && node)
    {
        rr = malloc(sizeof(*rr));
        if (rr)
            rr->data = malloc(sizeof(char)*3);
        if (rr->data)
        {
            ((char*)(rr->data))[0] = 'r';
            ((char*)(rr->data))[1] = 'r';
            ((char*)(rr->data))[2] = '\0';
        }
        cdl_list->pf_insert_after(cdl_list, node, rr);
    }
}

void iter_ops_ra(t_circular_double_link_list * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node)
{
    cdl_node_r[0] = *cdl_node;
    count_ops_r(cdl_list, &cdl_node_r[0], &count_r[0], 'a');
    cdl_node_r[1] = cdl_node_r[0];
    count_ops_r(cdl_list, &cdl_node_r[1], &count_r[1], 'b');
    *cdl_node = cdl_node_r[1];
}

void iter_ops_rb(t_circular_double_link_list * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node)
{
    cdl_node_r[1] = *cdl_node;
    count_ops_r(cdl_list, &cdl_node_r[1], &count_r[0], 'b');
    cdl_node_r[0] = cdl_node_r[1];
    count_ops_r(cdl_list, &cdl_node_r[0], &count_r[1], 'a');
    *cdl_node = cdl_node_r[0];
}

void del_r(t_circular_double_link_list * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, size_t * count_rr)
{
    while (count_r[0] && count_r[1])
    {
        cdl_list->pf_delete_node(cdl_list, cdl_node_r[0]->previous);
        cdl_list->pf_delete_node(cdl_list, cdl_node_r[1]->previous);
        --count_r[1];
        --count_r[0];
        ++(*count_rr);
    }
}
