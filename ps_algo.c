/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/05 20:20:56 by kgriset          ###   ########.fr       */
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

void cdl_bottom_up_merge(int * array,t_circular_double_link_list *cdll_a, t_i i, int * array_cpy, t_circular_double_link_list *cdll_b)
{
    size_t j;
    size_t k;
    size_t l;

    k = i.left;
    j = i.right;
    l = i.left;
    while (k < i.end)
    {
        if (l < i.right && (j >= i.end || array[l] <= array[j]))
        {
            array_cpy[k] = array[l];
            push(cdll_b, cdll_a , 'b');
            rotate(cdll_b, 'b');
            ++l;
        }
        else if (l < i.right)
        {
            array_cpy[k] = array[j];
            rotate(cdll_a, 'a');

            push(cdll_b, cdll_a , 'b');
            rotate(cdll_b, 'b');

            r_rotate(cdll_a, 'a');
            ++j;
        }
        else
        {
            array_cpy[k] = array[j];
            push(cdll_b, cdll_a , 'b');
            rotate(cdll_b, 'b');
        }
        print_cdl(cdll_a);
        print_cdl(cdll_b);
        ++k;
    }
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

int cdl_bottom_up_merge_sort(t_circular_double_link_list * cdll_a,t_circular_double_link_list * cdll_b)
{
    int * array_cpy;
    int * array;
    size_t width;
    size_t n = cdll_a->total;
    t_i i;

    array = cdl2array(cdll_a);
    array_cpy = cdl2array(cdll_a);
    if (!(array_cpy && array))
        return(free(array), free(array_cpy), ERROR);
    width = 1;
    while (width < 2)
    {
        cdl2array_cpy(array, cdll_a);
        cdl2array_cpy(array_cpy, cdll_b);

        i.left = 0;
        while (i.left < n)
        {
            i.right = min_size_t(i.left + width, n); 
            i.end = min_size_t(i.left + 2*width, n);
            cdl_bottom_up_merge(array,cdll_a, i, array_cpy,cdll_b);
            i.left += 2*width;
        }
        width *= 2;
        // update_merge(&width, &array, &array_cpy);
    }
    // if (n % 2 == 0)
    //     return (ft_memcpy(array_cpy, array, n * sizeof(int))
    //         , free(array), array_cpy);
    // else
    //     return (free(array_cpy), array);
    return(free(array), free(array_cpy), SUCCESS);
}


