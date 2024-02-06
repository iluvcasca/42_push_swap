/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/06 20:36:28 by kgriset          ###   ########.fr       */
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

void cdl_bottom_up_merge(int * array,t_circular_double_link_list *cdll_a, t_cdl_i i, int * array_cpy, t_circular_double_link_list *cdll_b)
{
    size_t j;
    size_t k;
    size_t l;
    char direction;

    k = i.bottom;
    j = i.bottom;
    l = i.bottom;
    direction = 'r';

    if (cdll_a->total == cdll_b->total)
        direction = 'l';
    while (k < i.end)
    {
        if (l < i.left && (j >= i.right || array[l] >= array_cpy[j]))
        {
            r_rotate(cdll_a, 'a');
            if (direction == 'r')
                push(cdll_b, cdll_a, 'b');
            ++l;
        }
        else
        {
            r_rotate(cdll_b, 'b');
            if (direction == 'l')
                push(cdll_a, cdll_b, 'b');
            ++j;
        }
        ++k;
        print_cdl(cdll_a);
        print_cdl(cdll_b);
    }
    if (direction == 'r')
        --(*(i.run_left));
    else
        --(*(i.run_right));
}

int cdl_bottom_up_merge_sort(t_circular_double_link_list * cdll_a,t_circular_double_link_list * cdll_b)
{
    int * array_cpy;
    int * array;
    size_t width;
    size_t n = cdll_a->total;
    size_t run_right;
    size_t run_left;
    t_cdl_i i;

    i.run_right = &run_right;
    i.run_left = &run_left;
    deal(cdll_a, cdll_b);
    print_cdl(cdll_a);
    print_cdl(cdll_b);

    width = 2;
    run_left = n / 4;
    run_right = n / 4;
    while (width < n && cdll_a->total && cdll_b->total)
    {
        array = cdl2array(cdll_a);
        array_cpy = cdl2array(cdll_b);
        size_t max_a = cdll_a->total;
        size_t max_b = cdll_b->total;
        array_in_place_reverse(array, cdll_a->total);
        array_in_place_reverse(array_cpy, cdll_b->total);

        i.bottom = 0;
        while (i.bottom < n / 2)
        {
            i.right = min_size_t(i.bottom + width, max_a); 
            i.left = min_size_t(i.bottom + width, max_b); 
            i.end = min_size_t(i.bottom + 2*width, n/2);
            cdl_bottom_up_merge(array,cdll_a, i, array_cpy,cdll_b);
            i.bottom += width;
        }
        width *= 2;
        free(array);
        free(array_cpy);
    }
    return (SUCCESS);
}


