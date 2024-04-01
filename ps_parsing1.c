/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:16:33 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 13:11:50 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int check_duplicate(t_circular_db_ll * cdl_list)
{
    int * array;
    size_t i;

    array = cdl2array(cdl_list);
    i = 0;
    if (!array)
        return (ERROR);
    array = bottom_up_merge_sort(array, cdl_list->total);
    if (!array)
        return (ERROR);
    while (i < cdl_list->total - 1)
    {
        if (array[i] == array [i+1])
            return (free(array), ERROR);
        i++;
    }
    return (free(array), SUCCESS);
}
