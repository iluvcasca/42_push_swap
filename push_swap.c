/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:58:30 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/02 18:52:59 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int main(int argc, char ** argv)
{
    t_circular_double_link_list cdl_list;
    int status;

    cdl_init_list(&cdl_list);
    if (argc > 1)
        status = parse_input(argc, argv, &cdl_list); 
    else
        return (ERROR);
    if (status)
        cdl_free_list(&cdl_list);
    return (SUCCESS);
}
