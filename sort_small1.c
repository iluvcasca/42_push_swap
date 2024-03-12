/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:09:08 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/12 20:09:20 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int sort_small(t_vars * vars)
{
    if (vars->cdl_list_a->total == 3)
        return(fast_sort(vars), print_cdl_str(vars->ops), 
        free_all(vars),SUCCESS);
    else if (vars->cdl_list_a->total == 2)
        return(swap(vars->cdl_list_a,'a',vars->ops), print_cdl_str(vars->ops), 
        free_all(vars),SUCCESS);
    else
    {
        push_n(vars->cdl_list_b, vars->cdl_list_a, 'b', 2, vars->ops);
        push_n(vars->rank_b, vars->rank_a, 0, 2, vars->ops);
        fast_sort(vars);
        sort(vars);
        cdl_free_list(vars->rank_a);
        rank(vars->cdl_list_a, vars->rank_a);
        reorder(vars->cdl_list_a, vars->rank_a, vars->ops);
        cdl_free_list(vars->rank_a);
        rank(vars->cdl_list_a, vars->rank_a);
        optimize_ops_r(vars->ops);
        optimize_ops_rr(vars->ops);
        print_cdl_str(vars->ops);
        return(free_all(vars),SUCCESS);
    }
}
