/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:58:30 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/09 11:49:27 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int main(int argc, char ** argv)
{
    t_circular_double_link_list cdl_list_a;
    t_circular_double_link_list cdl_list_b; // how much can the stack handle

    int status;
    
    // argc = 2;
    // argv[1] = "31 129 67 55 576 308 71 72 215 643 682 363 18 326 30 377";
    // argv[1] = "12 475 562 22 397 285 135 215 56 603 432 100 293";
    // argv[1] = "132 627 533 574 438 174 582 591 310 4 367 89 494 275 15 445 434 142 362 640 408";
    char * s = "----------------------------\n";
    //
    cdl_init_list(&cdl_list_a);
    cdl_init_list(&cdl_list_b);
    if (argc > 1)
        status = parse_input(argc, argv, &cdl_list_a); 
    else
        return (ERROR);
    //
    t_run * run_a = malloc(sizeof(*run_a));
    t_run * run_b = malloc(sizeof(*run_b));
    if (status)
    {
        int * array = cdl2array(&cdl_list_a);
        // array = bottom_up_merge_sort(array, cdl_list_a.total);
        ft_printf("%sInput\n%s", s, s);
        print_cdl(&cdl_list_a);
        // ft_printf("%sParse Sort\n%s", s, s);
        // print_array(array, cdl_list_a.total);
        ft_printf("%sOPS\n%s", s, s);

        deal(&cdl_list_a, &cdl_list_b);
        set_run(&cdl_list_a, run_a);
        set_run(&cdl_list_b, run_b);
        print_cdl(&cdl_list_a);
        print_cdl(&cdl_list_b);
         
        print_map(run_a);
        ft_printf("%u\n", run_a->run_nb);
        print_map(run_b);
        ft_printf("%u\n", run_b->run_nb);

        free(run_a->map);
        free(run_b->map);
        deal2(&cdl_list_a,run_a, 'a');
        deal2(&cdl_list_b, run_b, 'b');
        set_run(&cdl_list_a, run_a);
        set_run(&cdl_list_b, run_b);

        print_cdl(&cdl_list_a);
        print_map(run_a);
        ft_printf("%u\n", run_a->run_nb);
        print_cdl(&cdl_list_b);
        print_map(run_b);
        ft_printf("%u\n", run_b->run_nb);
         
        free (run_a->map);
        free (run_b->map);
        cdl_bottom_up_merge_sort(&cdl_list_a,run_a,&cdl_list_b, run_b);

        free (array);
        free (run_a->map);
        free (run_b->map);

        set_run(&cdl_list_a, run_a);
        set_run(&cdl_list_b, run_b);

        print_cdl(&cdl_list_a);
        print_map(run_a);
        ft_printf("%u\n", run_a->run_nb);
        print_cdl(&cdl_list_b);
        print_map(run_b);
        ft_printf("%u\n", run_b->run_nb);

        free (run_a->map);
        free (run_b->map);

        cdl_free_list(&cdl_list_a);
        cdl_free_list(&cdl_list_b);
    }
    return (free(run_a),free(run_b),SUCCESS);
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
