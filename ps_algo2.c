/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:16:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/11 18:44:13 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void rotate_n_both(t_vars * vars, int * mov)
{
    rotate_n(vars->cdl_list_a, 'a', mov[0], vars->ops);
    rotate_n(vars->rank_a, 0, mov[0], vars->ops);
}

static void r_rotate_n_both(t_vars * vars, int * mov)
{
    r_rotate_n(vars->cdl_list_a, 'a', mov[0]*-1, vars->ops);
    r_rotate_n(vars->rank_a, 0, mov[0]*-1, vars->ops);
}

void sort(t_vars * vars)
{
    int * mov;
    int count;

    while (vars->cdl_list_b->total)
    {
        mov = compute_mov(vars);
        if (mov[0] >= 0)
            rotate_n_both(vars, mov);
        else
            r_rotate_n_both(vars, mov);
        if (mov[1] >= 0)
        {
            rotate_n(vars->cdl_list_b, 'b', mov[1], vars->ops);
            rotate_n(vars->rank_b, 0, mov[1], vars->ops);
        }
        else
        {
            r_rotate_n(vars->cdl_list_b, 'b', mov[1]*-1, vars->ops);
            r_rotate_n(vars->rank_b, 0, mov[1]*-1, vars->ops);
        }
        push(vars->cdl_list_a, vars->cdl_list_b, 'a', vars->ops);
        push(vars->rank_a, vars->rank_b, 0, vars->ops);
        free(mov);
    }
}

void reorder(t_circular_double_link_list * cdll_a, t_circular_double_link_list * rank_a, t_circular_double_link_list * ops)
{
    size_t i;
    int * array_a;

    i = 0;
    array_a = cdl2array(rank_a);
    while (i < cdll_a->total && array_a[i] != 0)
        ++i;
    if (i > cdll_a->total / 2)
        r_rotate_n(cdll_a, 'a', (size_t){(i - cdll_a->total)*-1}, ops);
    else
        rotate_n(cdll_a, 'a', i, ops);
    free(array_a);
}
