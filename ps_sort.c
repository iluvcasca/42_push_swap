/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:35:51 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/03 16:45:50 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void bottom_up_merge_sort(t_circular_double_link_list * cdl, size_t n)
{
    size_t width;
    size_t i;

    width = 1;
    while (width < n)
    {
        i = 0;
        while (i < n)
        {
            i += 2*width;
        }
        width *= 2;
    }

}
