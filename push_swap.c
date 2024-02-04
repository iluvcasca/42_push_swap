/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:58:30 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/04 17:41:01 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int main(int argc, char ** argv)
{
    t_circular_double_link_list cdl_list;
    int status;
    
    // argc = 2;
    // argv[1] = "";
    cdl_init_list(&cdl_list);
    if (argc > 1)
        status = parse_input(argc, argv, &cdl_list); 
    else
        return (ERROR);
    //
    if (status)
    {
        ft_printf("\n");
        int * array = cdl2array(&cdl_list);
        array = bottom_up_merge_sort(array, cdl_list.total);
        ft_printf("\n");
        for(size_t i = 0; i < cdl_list.total; ++i)
            ft_printf("%d\n", array[i]);
        free (array);
        cdl_free_list(&cdl_list);
    }
    return (SUCCESS);
}
