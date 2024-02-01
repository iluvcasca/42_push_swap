/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:58:30 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/01 15:32:14 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int main()
{
    int argc = 2;
    char * argv[2];
    argv[0] = "a.out";
    argv[1] = "2 1 3 6 5 8 ";
    t_circular_double_link_list cdl_list;
    int status = parse_input(argc, argv, &cdl_list); 
    if (!status)
        ft_printf("error\n");
    else
        ft_printf("success\n");
    return (1);
}
