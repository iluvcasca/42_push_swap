/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/11 17:17:05 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int * compute_mov(t_circular_double_link_list * cdll_a, t_circular_double_link_list * rank_a, t_circular_double_link_list * cdll_b, t_circular_double_link_list * rank_b)
{
    size_t i;
    size_t j;
    size_t sum_current;
    size_t sum;
    int * mov = malloc(sizeof(*mov) * 2);
    int * array_b;
    int * mov_b;
    int * array_a;
    int * mov_a;
    int insert = max_size(cdll_a->total, cdll_b->total);

    mov_b = cdl2array(cdll_b);
    array_b = cdl2array(rank_b);
    mov_a = cdl2array(cdll_a);
    array_a = cdl2array(rank_a);
    i = 0;
    while(i < cdll_b->total)
    {
        if (i <= cdll_b->total / 2)
            mov_b[i] = i;
        else
            mov_b[i] = i - (cdll_b->total);
        ++i;
    }
    i = 0;
    while(i < cdll_a->total)
    {
        if (i <= cdll_a->total / 2)
            mov_a[i] = i;
        else
            mov_a[i] = i - (cdll_a->total);
        ++i;
    }
    i = 0; 
    sum_current = max_size(cdll_b->total, cdll_a->total);
    while (i < cdll_b->total)
    {
        insert = max_size(cdll_a->total, cdll_b->total);
        j = 0;
        while (j < cdll_a->total)
        {
            if (abs(array_a[j] - array_b[i]) <= insert)
                insert = abs(array_a[j] - array_b[i]);
            ++j;
        }
        j = 0;
        while (j < cdll_a->total && abs(array_a[j] - array_b[i]) != insert)
        {
            ++j;
        }
        if (array_a[j] - array_b[i] < 0 && j + 1 < cdll_a->total)
            ++j;
        else if (array_a[j] - array_b[i] < 0 && j + 1 == cdll_a->total)
            j = 0;
        if (mov_a[j] < 0 && mov_b[i] < 0)
            sum = max_size((size_t){mov_a[j]*-1}, (size_t){mov_b[i]*-1}); 
        else if (mov_a[j] >= 0 && mov_b[i] < 0)
            sum = mov_a[j] + mov_b[i]*-1;
        else if (mov_a[j] < 0 && mov_b[i] >= 0)
            sum = mov_b[i] + mov_a[j]*-1;
        else
            sum = max_size((size_t)mov_a[j],(size_t)mov_b[i]);
        if (sum < sum_current)
        {
            sum_current = sum;
            mov[0] = mov_a[j]; 
            mov[1] = mov_b[i]; 
        }
        ++i; 
    }
    return (free(array_a), free(array_b), free(mov_a), free(mov_b), mov);
}
