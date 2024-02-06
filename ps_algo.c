/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/06 17:20:21 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void cdl_update_merge(size_t * width, int ** array, int ** array_cpy)
{
    int * temp;

    *width *= 2;
    temp = *array;
    *array = *array_cpy;
    *array_cpy = temp;
}

void cdl_bottom_up_merge(int * array,t_circular_double_link_list *cdll_a, t_i i, int * array_cpy, t_circular_double_link_list *cdll_b, size_t max_lena, size_t max_lenb)
{
    size_t j;
    size_t k;
    size_t l;
    char merge_dir;

    k = i.left;
    // j = i.right;
    // l = i.left;
    l = i.left;
    j = i.left;

    if (cdll_a->total > cdll_b->total)
        merge_dir = 'r';
    else
        merge_dir = 'l';

    while (k < i.end)
    {
        if (l < min_size_t(i.right,max_lena) && (j >= min_size_t(i.right,max_lenb) || array[l] <= array_cpy[j]))
        {
            // array_cpy[k] = array[l];
            if (merge_dir == 'r')
            {
                r_rotate(cdll_a, 'a');
                push(cdll_b, cdll_a, 'b');
            }
            else
                r_rotate(cdll_a, 'a');
            ++l;
        }
        else
        {
            // array_cpy[k] = array[j];
            if (merge_dir == 'r')
                r_rotate(cdll_b, 'b');
            else
            {
                r_rotate(cdll_b, 'b');
                push(cdll_a, cdll_b, 'b');
            }
            ++j;
        }
        print_cdl(cdll_a);
        print_cdl(cdll_b);
        ++k;
    }
}

size_t max(size_t a, size_t b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int * cdl2array_cpy(int * array, t_circular_double_link_list * cdl_list)
{
    t_double_link_node * cdl_node;
    size_t i;

    i = 0;
    cdl_node = cdl_list->first_node;
    if (array && cdl_list->first_node)
    {
        do {
            array[i] = *((int *)cdl_node->data);
            cdl_node = cdl_node->next;
            ++i;
        } while (cdl_node != cdl_list->first_node);
    }
    return (array);
}

void deal(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b)
{
    size_t n;
    int * array;
    t_i i;
    
    n = cdll_a->total;
    array = cdl2array(cdll_a);
    if (!array)
        return;
    i.left = 0;
    while (i.left + 2*(n%2) < n)
    {
        i.right = min_size_t(i.left + 1, n); 

        if (array[i.left] <= array[i.right])
        {
            if (cdll_b->total >= n / 2)
            {
                swap(cdll_a, 'a');
                rotate(cdll_a, 'a');
                rotate(cdll_a, 'a');
            }
            else
            {
                push(cdll_b, cdll_a, 'b');
                push(cdll_b, cdll_a, 'b');
            }
        }
        else
        {
            if (cdll_b->total < n / 2)
            {
                swap(cdll_a, 'a');
                push(cdll_b, cdll_a, 'b');
                push(cdll_b, cdll_a, 'b');
            }
            else
            {
                rotate(cdll_a, 'a');
                rotate(cdll_a, 'a');
            }
        }
        print_cdl(cdll_a);
        print_cdl(cdll_b);


        i.left += 2;
    }
    free(array);
}

int cdl_bottom_up_merge_sort(t_circular_double_link_list * cdll_a,t_circular_double_link_list * cdll_b)
{
    int * array_cpy;
    int * array;
    size_t width;
    size_t n = cdll_a->total;
    t_i i;

    deal(cdll_a, cdll_b);
    print_cdl(cdll_a);
    print_cdl(cdll_b);

    width = 2;
    while (width < n)
    {
        array = cdl2array(cdll_a);
        array_cpy = cdl2array(cdll_b);
        size_t max_lena = cdll_a->total;
        size_t max_lenb = cdll_b->total;
        if (!(array_cpy && array))
            return(free(array), free(array_cpy), ERROR);
        array_in_place_reverse(array_cpy, cdll_b->total);
        array_in_place_reverse(array, cdll_a->total);
        i.left = 0;
        while (i.left < n / 2)
        {
            i.right = min_size_t(i.left + width, n); 
            i.end = min_size_t(i.left + 2*width, n);
            if (i.end > max(cdll_a->total, cdll_b->total))
                --i.end;
            cdl_bottom_up_merge(array,cdll_a, i, array_cpy,cdll_b, max_lena, max_lenb);
            i.left += width;
        }
        width *= 2;
        free(array);
        free(array_cpy);
        // update_merge(&width, &array, &array_cpy);
    }
    if (cdll_b->total)
        push(cdll_a, cdll_b, 'a');
    else
        r_rotate(cdll_a, 'a');
    // if (n % 2 == 0)
    //     return (ft_memcpy(array_cpy, array, n * sizeof(int))
    //         , free(array), array_cpy);
    // else
    //     return (free(array_cpy), array);
    // while (*((int *)cdll_a->first_node->data) >= *((int *)cdll_b->first_node->next->data))
    //     rotate(cdll_a, 'a');

    return (SUCCESS);
}


