
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:24:27 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/11 15:35:15 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

int main(int argc, char ** argv)
{
    t_circular_double_link_list cdl_list_a;
    t_circular_double_link_list cdl_list_b; // how much can the stack handle
    t_circular_double_link_list rank_a;
    t_circular_double_link_list rank_b;
    t_circular_double_link_list ops;
    int * array;

    int status;
    
    // argc = 2;
    // argv[1] = "2024 2492 4645 2514 4107 1871 1907 2586 789 1399";
    // argv[1] = "347 2770 3130 4420 2436 1600 2415 3690 1932 1589 3704 3217 2700 2854 4898 2442 3765 1886 126 1009 1400 1958 3063 445 4321 1125 3757 2733 1161 1121 3421 4585 2750 609 4869 4713 213 960 3798 1393 3864 2852 3114 3981 3160 2689 165 636 3243 4261 2648 2940 3248 304 3370 4557 744 699 3144 4689 2553 2551 2187 1601 3127 1544 1362 2075 3814 4721 133 2999 3230 3594 3394 4252 4575 1769 3330 466 4266 808 548 1445 2407 4671 4229 3250 1933 4487 3937 3770 1722 4194 4901 1621 2546 4311 4065 1043";
    // char * s = "----------------------------\n";
    
    cdl_init_list(&cdl_list_a);
    cdl_init_list(&cdl_list_b);
    cdl_init_list(&rank_a);
    cdl_init_list(&rank_b);

    cdl_init_list(&ops);

    if (argc > 1)
        status = parse_input(argc, argv, &cdl_list_a); 
    else
        return (ERROR);
    //
    if (status)
    {
        // ft_printf("%sInput\n%s", s, s);
        // print_cdl(&cdl_list_a);

        rank(&cdl_list_a, &rank_a);

        // print_cdl(&rank_a);

        array = lis(&cdl_list_a);
        // print_array(array, cdl_list_a.total);

        deal(&cdl_list_a, &rank_a, &cdl_list_b, &rank_b, array, &ops);
        // print_cdl(&rank_a);
        // print_cdl(&rank_b);
        sort(&cdl_list_a, &rank_a, &cdl_list_b, &rank_b, &ops);
        cdl_free_list(&rank_a);
        rank(&cdl_list_a, &rank_a);
        // print_cdl(&rank_a);
        reorder(&cdl_list_a, &rank_a, &ops);
        cdl_free_list(&rank_a);
        rank(&cdl_list_a, &rank_a);
        // print_cdl(&rank_a);
        // print_cdl_str(&ops);
        optimize_ops_r(&ops);
        optimize_ops_rr(&ops);
        
        // ft_printf("\nopti\n\n\n");
        print_cdl_str(&ops);
        free(array);
        cdl_free_list(&ops);
        cdl_free_list(&rank_a);
        cdl_free_list(&cdl_list_a);
        cdl_free_list(&cdl_list_b);
        cdl_free_list(&rank_b);
    }
    return (SUCCESS);
}

