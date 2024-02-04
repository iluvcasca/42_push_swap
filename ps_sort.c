/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:35:51 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/04 17:13:15 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int * bottom_up_merge_sort(int * array, size_t n)
{
    int * array_cpy;
    size_t width;
    t_i i;

    width = 1;
    array_cpy = malloc(sizeof(*array_cpy) * n);
    if (!array_cpy)
        return (array_cpy);
    while (width < n)
    {
        i.left = 0;
        while (i.left < n)
        {
            i.right = min_size_t(i.left + width, n); 
            i.end = min_size_t(i.left + 2*width, n);
            bottom_up_merge(array, i, array_cpy);
            i.left += 2*width;
        }
        update_merge(&width, &array, &array_cpy);
    }
    if (n % 2 == 0)
        return (ft_memcpy(array_cpy, array, n * sizeof(int)), free(array), array_cpy);
    else
        return (free(array_cpy), array);
}

void update_merge(size_t * width, int ** array, int ** array_cpy)
{
    int * temp;

    *width *= 2;
    temp = *array;
    *array = *array_cpy;
    *array_cpy = temp;
}

void bottom_up_merge(int * array, t_i i, int * array_cpy)
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
            ++l;
        }
        else
        {
            array_cpy[k] = array[j];
            ++j;
        }
        ++k;
    }
}

size_t min_size_t(size_t a, size_t b)
{
    if (a <= b)
        return (a);
    else
        return (b);
}
