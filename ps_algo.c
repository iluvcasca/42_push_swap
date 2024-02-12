/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/12 19:45:38 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int rank(t_circular_double_link_list * cdll, t_circular_double_link_list * rank)
{
    int * array;
    t_double_link_node * node;
    t_double_link_node * rank_node;
    size_t i;

    array = cdl2array(cdll);
    array = bottom_up_merge_sort(array, cdll->total);
    i = 0;
    node = cdll->first_node;
    do {
        while (*((int *)node->data) != array[i])
            ++i;
        if (!add_int2node(rank, rank_node, i))
            return(cdl_free_list(cdll),cdl_free_list(rank),free(array),ERROR);
        node = node->next;
        i = 0;
    } while (node != cdll->first_node);
    return (free(array),SUCCESS);
}

int * lis(t_circular_double_link_list * cdll_a)
{
    int * lis = malloc(sizeof(*lis) * cdll_a->total);
    int * cdl_array = cdl2array(cdll_a);
    int lis_count[cdll_a->total];
    int i = 0;
    size_t j = 0;
    size_t lis_max = 1;
    size_t lis_max_index = 0;

    ft_memset(lis, 0, sizeof(*lis) * cdll_a->total);
    while (i < cdll_a->total)
    {
        lis_count[i] = 1;
        j = 0;
        while (j < i)
        {
            if (cdl_array[i] > cdl_array[j] && lis_count[i] < lis_count[j] + 1) 
                lis_count[i] = lis_count[j] + 1;
            ++j;
        }
        ++i;
    }
    i = 0;
    while (i < cdll_a->total)
    {
        if (lis_max < lis_count[i])
        {
            lis_max = lis_count[i];
            lis_max_index = i;
        }
        // ft_printf("%d,",lis_count[i]);
        i++;
    }
    // ft_printf("\n");
    i = lis_max_index;
    j = lis_max - 1;
    lis[j--] = cdl_array[i];
    while (i >= 0)
    {
        if (lis_count[i] == lis_max - 1)
        {
            lis[j] = cdl_array[i];
            lis_max = lis_count[i];
            --j;
        }
        --i;
    }
    return (free(cdl_array),lis);
}

int deal(t_circular_double_link_list * cdll_a, t_circular_double_link_list * rank_a, t_circular_double_link_list * cdll_b, t_circular_double_link_list * rank_b, int * lis)
{
    size_t i;
    size_t j;
    size_t n;
    int * array;

    i = 0;
    j = 0;
    n = cdll_a->total;
    array = cdl2array(cdll_a);
    
    while (i < n)
    {
        if (array[i] == lis[j])
        {
            rotate(cdll_a, 'a');
            rotate(rank_a, 0);
            ++j;
        }
        else
        {
            push(cdll_b, cdll_a, 'b');
            push(rank_b, rank_a, 0);
        }
        ++i;
    }
    return (free(array), SUCCESS); 
}

int sort(t_circular_double_link_list * cdll_a ,t_circular_double_link_list * rank_a,t_circular_double_link_list *cdll_b, t_circular_double_link_list * rank_b)
{
    int * mov;
    int count;

    while (cdll_b->total)
    {
        mov = compute_mov(cdll_a, rank_a, cdll_b, rank_b);
        if (mov[0] >= 0)
        {
            rotate_n(cdll_a, 'a', mov[0]);
            rotate_n(rank_a, 0, mov[0]);
        }
        else
        {
            r_rotate_n(cdll_a, 'a', mov[0]*-1);
            r_rotate_n(rank_a, 0, mov[0]*-1);
        }
        if (mov[1] >= 0)
        {
            rotate_n(cdll_b, 'b', mov[1]);
            rotate_n(rank_b, 0, mov[1]);
        }
        else
        {
            r_rotate_n(cdll_b, 'b', mov[1]*-1);
            r_rotate_n(rank_b, 0, mov[1]*-1);
        }
        push(cdll_a, cdll_b, 'a');
        push(rank_a, rank_b, 0);
        free(mov);
        // print_cdl(rank_a);
        // print_cdl(rank_b);
    }
    return(SUCCESS);
}
void reorder(t_circular_double_link_list * cdll_a, t_circular_double_link_list * rank_a)
{
    size_t i;
    int * array_a;

    i = 0;
    array_a = cdl2array(rank_a);
    while (i < cdll_a->total && array_a[i] != 0)
        ++i;
    if (i > cdll_a->total / 2)
        r_rotate_n(cdll_a, 'a', (size_t){(i - cdll_a->total)*-1});
    else
        rotate_n(cdll_a, 'a', i);
    free(array_a);
}

int abs(int a)
{
    if (a < 0)
        return (a*-1);
    return (a);
}

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
        // if (j == cdll_a->total)
        //     j = 0;
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

size_t max_size(size_t a, size_t b)
{
    if (a >= b)
        return a;
    else
        return b;
}
