/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:24:27 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/12 19:45:15 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

int main(int argc, char ** argv)
{
    t_circular_double_link_list cdl_list_a;
    t_circular_double_link_list cdl_list_b; // how much can the stack handle
    t_circular_double_link_list rank_a;
    t_circular_double_link_list rank_b;
    int * array;

    int status;
    
    // argc = 2;
    // argv[1] = "3173 2068 4853 4935 1257 4198 4945 2383 4363 2140 550 2170 682 2137 3586";
    // argv[1] = "4499 813 4133 3119 3397 140 4759 3676 3300 1551";
    // argv[1] = "2024 2492 4645 2514 4107 1871 1907 2586 789 1399";
    // argv[1] = "347 2770 3130 4420 2436 1600 2415 3690 1932 1589 3704 3217 2700 2854 4898 2442 3765 1886 126 1009 1400 1958 3063 445 4321 1125 3757 2733 1161 1121 3421 4585 2750 609 4869 4713 213 960 3798 1393 3864 2852 3114 3981 3160 2689 165 636 3243 4261 2648 2940 3248 304 3370 4557 744 699 3144 4689 2553 2551 2187 1601 3127 1544 1362 2075 3814 4721 133 2999 3230 3594 3394 4252 4575 1769 3330 466 4266 808 548 1445 2407 4671 4229 3250 1933 4487 3937 3770 1722 4194 4901 1621 2546 4311 4065 1043";
    // argv[1] = "31 129 67 55 576 308 71";
    // argv [1] = "1974 200 2064 1283 3655 727 314 1899 1115 375 2095 1348 4806 789 452 3288 1775 3784 819 3973 513 3385 4921 2966 3979 2862 2015 4625 4756 3278";
    // argv[1] = "12 475 562 22 397 285 135 215 56 603 432 100 293";
    // argv[1] = "627 533 574 438 174 582 591 310 4 367 89 494 275 15 445 434 142 362 640 408";
    char * s = "----------------------------\n";
    //
    cdl_init_list(&cdl_list_a);
    cdl_init_list(&cdl_list_b);
    cdl_init_list(&rank_a);
    cdl_init_list(&rank_b);

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

        deal(&cdl_list_a, &rank_a, &cdl_list_b, &rank_b, array);
        // print_cdl(&rank_a);
        // print_cdl(&rank_b);
        sort(&cdl_list_a, &rank_a, &cdl_list_b, &rank_b);
        cdl_free_list(&rank_a);
        rank(&cdl_list_a, &rank_a);
        // print_cdl(&rank_a);
        reorder(&cdl_list_a, &rank_a);
        cdl_free_list(&rank_a);
        rank(&cdl_list_a, &rank_a);
        // print_cdl(&rank_a);

        free(array);
        cdl_free_list(&rank_a);
        cdl_free_list(&cdl_list_a);
        cdl_free_list(&cdl_list_b);
        cdl_free_list(&rank_b);
    }
    return (SUCCESS);
}

void print_array(int * array, size_t size)
{
    size_t i;
    
    i = 0;
    ft_printf("\n");
    while (i < size)
    {
        ft_printf("%d\n", array[i]);
        ++i;
    }
}

void print_map(t_run * run)
{
    size_t i;
    size_t n;

    i = run->map_size;
    n = i;
    --i;
    ft_printf("\n");
    while (n)
    {
        ft_printf("%c\n", run->map[i]);
        --i;
        --n;
    }
}

void print_cdl(t_circular_double_link_list * cdl_list)
{
    t_double_link_node * cdl_node;

    if (cdl_list && cdl_list->first_node)
    {
        ft_printf("\n");
        cdl_node = cdl_list->first_node;
        do {
            ft_printf("%d\n", *((int *)cdl_node->data));
            cdl_node = cdl_node->next;
        } while (cdl_node != cdl_list->first_node);
    }
    if (cdl_list)
        ft_printf("total: %u\n", cdl_list->total);
}
