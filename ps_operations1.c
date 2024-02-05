/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_operations1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:14:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/05 19:55:36 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int r_rotate(t_circular_double_link_list * cdl_list, char list_name)
{
    if (!(cdl_list && cdl_list->first_node))
        return (ERROR);
    cdl_list->first_node = cdl_list->last_node;
    cdl_list->last_node = cdl_list->last_node->previous;
    if (list_name)
        ft_printf("rr%c\n", list_name);
    return (SUCCESS);
}

void r_rr(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b)
{
    r_rotate(cdll_a, 0);
    r_rotate(cdll_b, 0);
    ft_printf("rrr\n");
}

void r_rotate_n(t_circular_double_link_list * cdl_list, char list_name, size_t n)
{
    size_t i;

    i = 0;
    while(i < n)
    {
        r_rotate(cdl_list, list_name);
        ++i;
    }
}

void rotate_n(t_circular_double_link_list * cdl_list, char list_name, size_t n)
{
    size_t i;

    i = 0;
    while(i < n)
    {
        rotate(cdl_list, list_name);
        ++i;
    }
}

void push_n(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b, char list_name, size_t n)
{
    size_t i;

    i = 0;
    while(i < n)
    {
        push(cdll_a, cdll_b, list_name);
        ++i;
    }
}
