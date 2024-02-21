/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/21 17:46:29 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stddef.h>
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
void compute_mov3(size_t i, int * insert, t_cdll_pair * cdll, t_array_pair * array)
{
    size_t j;

    *insert = max_size(cdll->a->total, cdll->b->total);
    j = 0;
    while (j < cdll->a->total)
    {
        if (abs(array->a[j] - array->b[i]) <= *insert)
            *insert = abs(array->a[j] - array->b[i]);
        ++j;
    }
}

void compute_mov2(size_t i, size_t j,t_array_pair * mov_, size_t * csum_sum)
{
    if (mov_->a[j] < 0 && mov_->b[i] < 0)
        csum_sum[1] = max_size((size_t){mov_->a[j]*-1}, (size_t){mov_->b[i]*-1}); 
    else if (mov_->a[j] >= 0 && mov_->b[i] < 0)
        csum_sum[1] = mov_->a[j] + mov_->b[i]*-1;
    else if (mov_->a[j] < 0 && mov_->b[i] >= 0)
        csum_sum[1] = mov_->b[i] + mov_->a[j]*-1;
    else
        csum_sum[1] = max_size((size_t)mov_->a[j],(size_t)mov_->b[i]);
}

void compute_mov4(size_t * j, size_t * i, t_array_pair * array, t_cdll_pair * cdll)
{
    if (array->a[*j] - array->b[*i] < 0 && *j + 1 < cdll->a->total)
        ++(*j);
    else if (array->a[*j] - array->b[*i] < 0 && *j + 1 == cdll->a->total)
        *j = 0;
}

void compute_mov5(t_array_pair * mov_, int * mov, size_t i, size_t j)
{
    mov[0] = mov_->a[j]; 
    mov[1] = mov_->b[i]; 
}

int compute_mov6(size_t * i, t_cdll_pair * cdll, int * insert, size_t ** csum_sum)
{
    *i = 0; 
    *insert = max_size(cdll->a->total, cdll->b->total);
    *csum_sum = malloc(sizeof(*csum_sum)*2);
    if (!*csum_sum)
        return 0;
    (*csum_sum)[0] = max_size(cdll->b->total, cdll->a->total);
    return 1;
}

void compute_mov1(t_cdll_pair * cdll, t_array_pair * mov_,t_array_pair * array, int * mov)
{
    size_t j;
    size_t i;
    size_t * csum_sum;
    int insert;

    if (!compute_mov6(&i, cdll, &insert, &csum_sum))
        return;
    while (i < cdll->b->total)
    {
        compute_mov3(i, &insert, cdll, array);
        j = 0;
        while (j < cdll->a->total && abs(array->a[j] - array->b[i]) != insert)
            ++j;
        compute_mov4(&j, &i, mov_, cdll);
        compute_mov2(i, j, mov_, csum_sum);
        if (csum_sum[1] < csum_sum[0])
        {
            csum_sum[0] = csum_sum[1];
            compute_mov5(mov_, mov, i, j);
        }
        ++i; 
    }
    free(csum_sum);
}

int * compute_mov(t_cdll_pair * cdll, t_cdll_pair * rank)
{
    int * mov = malloc(sizeof(*mov) * 2);
    t_array_pair array;
    t_array_pair mov_;

    mov_.b = cdl2array(cdll->b);
    array.b = cdl2array(rank->b);
    mov_.a = cdl2array(cdll->a);
    array.a = cdl2array(rank->a);
    get_distance(cdll->b, mov_.b);
    get_distance(cdll->a, mov_.a);  
    compute_mov1(cdll, &mov_, &array, mov); 
    return (free(array.a), free(array.b), free(mov_.a), free(mov_.b), mov);
}

size_t max_size(size_t a, size_t b)
{
    if (a >= b)
        return a;
    else
        return b;
}
