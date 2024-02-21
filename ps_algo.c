/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/21 10:49:22 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stdlib.h>

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

void count_lis(int * lis_count, int * cdl_array, size_t n)
{
    int i = 0;
    size_t j = 0;

    while (i < n)
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
}

void get_lis_max(size_t * max, int * lis_count, size_t n)
{
    int i = 0;

    while (i < n)
    {
        if (max[0] < lis_count[i])
        {
            max[0] = lis_count[i];
            max[1] = i;
        }
        ++i;
    }
}

void build_lis(size_t * max, int * lis_count, int * lis, int * cdl_array)
{
    int i;
    size_t j;

    i = max[1];
    j = max[0] - 1;
    lis[j--] = cdl_array[i];
    while (i >= 0)
    {
        if (lis_count[i] == max[0] - 1)
        {
            lis[j] = cdl_array[i];
            max[0] = lis_count[i];
            --j;
        }
        --i;
    }
}

int * lis(t_circular_double_link_list * cdll_a)
{
    int * lis = malloc(sizeof(*lis) * cdll_a->total);
    int * cdl_array = cdl2array(cdll_a);
    int * lis_count;
    size_t * max;

    max = malloc(sizeof(*max)*2);
    max[0] = 1;
    max[1] = 0;
    lis_count = malloc(sizeof(*lis_count) * cdll_a->total);
    ft_memset(lis, 0, sizeof(*lis) * cdll_a->total);
    count_lis(lis_count, cdl_array, cdll_a->total); 
    get_lis_max(max,lis_count, cdll_a->total);
    build_lis(max, lis_count, lis, cdl_array);
     
    return (free(cdl_array),free(lis_count),free(max),lis);
}

void rotate_cdll_rank(t_circular_double_link_list * cdll, t_circular_double_link_list * rank, char list_name, t_circular_double_link_list * ops)
{
    rotate(cdll, list_name, ops);
    rotate(rank, 0, ops);
}

void push_cdll_rank(t_cdll_pair * cdll, t_cdll_pair * rank, char list_name, t_circular_double_link_list * ops)
{
    if (list_name == 'b')
    {
        push(cdll->b,cdll->a, list_name, ops);
        push(rank->b,rank->a, 0, ops);
    }
    else
    {
        push(cdll->a,cdll->b, list_name, ops);
        push(rank->a,rank->b, 0, ops);
    }
}

int deal(t_cdll_pair * cdll, t_cdll_pair * rank, int * lis, t_circular_double_link_list * ops)
{
    size_t i;
    size_t j;
    size_t n;
    int * array;

    i = 0;
    j = 0;
    n = cdll->a->total;
    array = cdl2array(cdll->a);
    
    while (i < n)
    {
        if (array[i] == lis[j])
        {
            rotate_cdll_rank(cdll->a,rank->a, 'a', ops);
            ++j;
        }
        else
            push_cdll_rank(cdll, rank, 'b', ops);
        ++i;
    }
    return (free(array), SUCCESS); 
}

void rotate_n_cdll_rank_a(t_circular_double_link_list * cdll_a, t_circular_double_link_list * rank_a, int n, t_circular_double_link_list * ops)
{
    rotate_n(cdll_a, 'a', n, ops);
    rotate_n(rank_a, 0, n, ops);
}

void rotate_n_cdll_rank_b(t_circular_double_link_list * cdll_b, t_circular_double_link_list * rank_b, int n, t_circular_double_link_list * ops)
{
    rotate_n(cdll_b, 'b', n, ops);
    rotate_n(rank_b, 0, n, ops);
}

int sort(t_cdll_pair * cdll ,t_cdll_pair * rank, t_circular_double_link_list * ops)
{
    int * mov;
    int count;

    while (cdll->b->total)
    {
        mov = compute_mov(cdll, rank);
        if (mov[0] >= 0)
            rotate_n_cdll_rank_a(cdll->a, rank->a, mov[0] , ops);
        else
            rotate_n_cdll_rank_a(cdll->a, rank->a, -1 * mov[0] , ops);
        if (mov[1] >= 0)
            rotate_n_cdll_rank_a(cdll->b, rank->b, mov[1], ops);
        else
            rotate_n_cdll_rank_a(cdll->b, rank->b, -1 * mov[1], ops);
        push_cdll_rank(cdll, rank, 'a', ops);
        free(mov);
    }
    return(SUCCESS);
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

int abs(int a)
{
    if (a < 0)
        return (a*-1);
    return (a);
}

void get_distance(t_circular_double_link_list * cdll, int * mov)
{
    size_t i;

    i = 0;
    while(i < cdll->total)
    {
        if (i <= cdll->total / 2)
            mov[i] = i;
        else
            mov[i] = i - (cdll->total);
        ++i;
    }
}

int * compute_mov(t_cdll_pair * cdll, t_cdll_pair * rank)
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
    int insert = max_size(cdll->a->total, cdll->b->total);

    mov_b = cdl2array(cdll->b);
    array_b = cdl2array(rank->b);
    mov_a = cdl2array(cdll->a);
    array_a = cdl2array(rank->a);

    get_distance(cdll->b, mov_b);
    get_distance(cdll->a, mov_a);
    i = 0; 
    sum_current = max_size(cdll->b->total, cdll->a->total);
    while (i < cdll->b->total)
    {
        insert = max_size(cdll->a->total, cdll->b->total);
        j = 0;
        while (j < cdll->a->total)
        {
            if (abs(array_a[j] - array_b[i]) <= insert)
                insert = abs(array_a[j] - array_b[i]);
            ++j;
        }
        j = 0;
        while (j < cdll->a->total && abs(array_a[j] - array_b[i]) != insert)
        {
            ++j;
        }
        if (array_a[j] - array_b[i] < 0 && j + 1 < cdll->a->total)
            ++j;
        else if (array_a[j] - array_b[i] < 0 && j + 1 == cdll->a->total)
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
