/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/12 11:18:25 by kgriset          ###   ########.fr       */
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

void deal(t_circular_double_link_list * cdll_a, t_circular_double_link_list * rank_a, t_circular_double_link_list * cdll_b, t_circular_double_link_list * rank_b)
{
    size_t n;
    size_t i;
    t_circular_double_link_list * rank_temp;
    t_circular_double_link_list * garbage;

    rank_temp = malloc(sizeof(*rank_temp));
    garbage = malloc(sizeof(*garbage));
    cdl_init_list(rank_temp);
    cdl_init_list(garbage);
    while (cdll_a->total != 3)
    {
        n = cdll_a->total - 1;
        i = 0;
        rank(cdll_a, rank_temp);
        while(i <= n && cdll_a->total != 3)
        {
            size_t t = *((int *)rank_temp->first_node->data);
            if (*((int *)rank_temp->first_node->data) <= 2*(n/3) && *((int *)rank_temp->first_node->data) > n/3)
            {
                push(rank_b, rank_a, 0);
                push(cdll_b, cdll_a, 'b');
                push(garbage, rank_temp, 0);
            }
            else if (*((int *)rank_temp->first_node->data) <= 2*(n/3))
            {
                push(rank_b, rank_a, 0);
                push(garbage, rank_temp, 0);
                rotate(rank_b, 0);
                push(cdll_b, cdll_a, 'b');
                rotate(cdll_b, 'b');
            }
            else
            {
                rotate(rank_a, 0);
                rotate(rank_temp, 0);
                rotate(cdll_a, 'a');
            }
            ++i;    
        }
        cdl_free_list(rank_temp);
        // print_cdl(rank_a);
        // print_cdl(rank_b);
    }
    cdl_free_list(garbage);
    free(rank_temp);
    free(garbage);
}

void sort_3(t_circular_double_link_list * cdll_a, t_circular_double_link_list * rank_a)
{
    t_circular_double_link_list rank_temp;
    int * temp_rank;
   
    cdl_init_list(&rank_temp);
    rank(cdll_a, &rank_temp);
    temp_rank = cdl2array(&rank_temp);
    if (temp_rank[0] == 2 && temp_rank[1] == 1 && temp_rank[2] == 0)
    {
        swap(cdll_a, 'a');
        swap(rank_a, 0);
        r_rotate(cdll_a, 'a');
        r_rotate(rank_a, 0);
    }
    else if (temp_rank[0] == 1 && temp_rank[1] == 0 && temp_rank[2] == 2)
    {
        swap(cdll_a, 'a');
        swap(rank_a, 0);
    }
    else if (temp_rank[0] == 1 && temp_rank[1] == 2 && temp_rank[2] == 0)
    {
        r_rotate(cdll_a, 'a');
        r_rotate(rank_a, 0);
    }
    else if (temp_rank[0] == 2 && temp_rank[1] == 0 && temp_rank[2] == 1)
    {
        rotate(cdll_a, 'a');
        rotate(rank_a, 0);
    }
    else if (temp_rank[0] == 0 && temp_rank[1] == 2 && temp_rank[2] == 1)
    {
        rotate(cdll_a, 'a');
        rotate(rank_a, 0);
        swap(cdll_a, 'a');
        swap(rank_a, 0);
        r_rotate(cdll_a, 'a');
        r_rotate(rank_a, 0);
    }
    cdl_free_list(&rank_temp);
    free(temp_rank);
}

void sort(t_circular_double_link_list * cdll_a, t_circular_double_link_list * rank_a, t_circular_double_link_list * cdll_b, t_circular_double_link_list * rank_b)
{
    size_t top;
    size_t bottom;
    int current_top;
    int current_bottom;
    t_double_link_node * search_node;
    size_t bottom_el;
    size_t top_el;

    bottom_el = 0;
    top_el = 0;
    while (cdll_b->total)
    {
        print_cdl(rank_a);
        print_cdl(rank_b);

        top = 0;
        bottom = 0;
        if (*((int *)rank_a->first_node->data) != *((int *)rank_a->first_node->next->data) - 1)
        {
            rotate(rank_a, 0);
            rotate(cdll_a, 'a');
            ++top_el;
        }
        else if (*((int *)rank_a->last_node->data) != *((int *)rank_a->last_node->previous->data) + 1)
        {
            r_rotate(rank_a, 0);
            r_rotate(cdll_a, 'a');
            ++bottom_el;
        }
        current_top = *((int *)rank_a->first_node->data);
        current_bottom = *((int *)rank_a->last_node->data);
        search_node = rank_b->first_node;
        while (*((int *)search_node->data) != current_top - 1 
            && *((int *)search_node->data) != current_bottom + 1)
        {
            search_node = search_node->next;
            ++top;
        }
        search_node = rank_b->last_node;
        while (*((int *)search_node->data) != current_top - 1 
            && *((int *)search_node->data) != current_bottom + 1)
        {
            search_node = search_node->previous;
            ++bottom;
        }
        if (bottom < top)
        {
            r_rotate_n(cdll_b, 'b', bottom + 1);
            r_rotate_n(rank_b, 0, bottom + 1);
            push(cdll_a, cdll_b, 'a');
            push(rank_a, rank_b, 0);
        }
        else
        {
            rotate_n(cdll_b, 'b', top);
            rotate_n(rank_b, 0, top);
            push(cdll_a, cdll_b, 'a');
            push(rank_a, rank_b, 0);
        }
        if (*((int *)rank_a->first_node->data) == current_bottom + 1 && *((int *)rank_a->first_node->data) != current_top - 1)
        {
            rotate(cdll_a, 'a');
            rotate(rank_a, 0);
            ++bottom_el;
        }
        else if (*((int *)rank_a->last_node->data) == current_top - 1 && *((int *)rank_a->first_node->data) != current_bottom + 1)
        {
            r_rotate(cdll_a, 'a');
            r_rotate(rank_a, 0);
            ++top_el;
        }
        if (*((int *)rank_a->last_node->data) == *((int *)rank_a->first_node->data) - 1)
        {
            r_rotate_n(cdll_a, 'a', bottom_el);
            r_rotate_n(rank_a, 0, bottom_el);
            bottom_el = 0;
        }
        else if (*((int *)rank_a->first_node->data) == *((int *)rank_a->last_node->data) + 1)
        {
            rotate_n(cdll_a, 'a', top_el);
            rotate_n(rank_a, 0, top_el);
            top_el = 0;
        } 
    }
}
