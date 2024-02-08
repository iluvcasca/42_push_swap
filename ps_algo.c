/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/08 15:41:48 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void deal(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b)
{
    size_t n;
    size_t j = 0;
    int * array;

    n = cdll_a->total;
    array = cdl2array(cdll_a);
    if (!array)
        return;
    while (j + 1 < n)
    {
        if (array[j] < array[j+1])
        {
            rotate(cdll_a, 'a');
            rotate(cdll_a, 'a');
        }
        else
    {
            push(cdll_b, cdll_a, 'b');
            push(cdll_b, cdll_a, 'b');
        }
        j+=2;
    }
    while (cdll_a->total > cdll_b->total)
    {
        swap(cdll_a, 'a');
        push(cdll_b, cdll_a, 'b');
        push(cdll_b, cdll_a, 'b');
    }
    while (cdll_a->total < cdll_b->total)
    {
        swap(cdll_b, 'b');
        push(cdll_a, cdll_b, 'a');
        push(cdll_a, cdll_b, 'a');
    }
    free(array);
}

int set_run(t_circular_double_link_list * cdll_a, t_run * run_a, t_circular_double_link_list * cdll_b, t_run * run_b)
{
    int * array_a;
    int * array_b;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    run_a->map = malloc(sizeof(int)*cdll_a->total);
    run_a->map_size = cdll_a->total;
    run_a->run_nb = 0;
    run_b->map = malloc(sizeof(int)*cdll_b->total);
    run_b->map_size = cdll_b->total;
    run_b->run_nb = 0;

    array_a = cdl2array(cdll_a); 
    array_b = cdl2array(cdll_b); 
    if (!run_a->map || !run_b->map || !array_a || !array_b)
        return (free(run_a->map), free(run_b->map), free(array_a), free(array_b), ERROR);
    array_in_place_reverse(array_a, cdll_a->total);
    array_in_place_reverse(array_b, cdll_b->total);

    while (i < run_a->map_size)
    {
        j = i;
        while (j + 1 < run_a->map_size && array_a[j] >= array_a[j+1])
        {
            run_a->map[j] = '0';
            j++;
        }
        if (j == i)
        {
            run_a->map[i] = 'x';
            run_a->run_nb++;
        }
        else
        {
            run_a->map[i] = 's';
            run_a->map[j] = 'e';
            run_a->run_nb++;
        }
        i+=(j-i);
        i++;
    }

    i = 0;
    j = 0;
    while (i < run_b->map_size)
    {
        j = i;
        while (j + 1 < run_b->map_size && array_b[j] >= array_b[j+1])
        {
            run_b->map[j] = '0';
            j++;
        }
        if (j == i)
        {
            run_b->map[i] = 'x';
            run_b->run_nb++;
        }
        else
        {
            run_b->map[i] = 's';
            run_b->map[j] = 'e';
            run_b->run_nb++;
        }
        i+=(j-i);
        i++;
    }

    return (free(array_a), free(array_b), SUCCESS);
}

