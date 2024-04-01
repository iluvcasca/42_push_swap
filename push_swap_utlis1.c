/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utlis1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:02:46 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 14:11:49 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int check_sorted(t_vars * vars)
{
    size_t i;
    int * rank;

    i = 0;
    rank = cdl2array(vars->rank_a);
    while (i < vars->rank_a->total)
    {
        if (i != (size_t)rank[i])
            break;
        ++i;
    }
    if (i == vars->rank_a->total || vars->rank_a->total == 1)
        return (free(rank),ERROR);
    return (free(rank),SUCCESS);
}
