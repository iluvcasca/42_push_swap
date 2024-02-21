
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:24:27 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/21 10:11:59 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

int main(int argc, char ** argv)
{
    t_cdll_pair cdl_list;
    t_cdll_pair rank_;
    t_circular_double_link_list ops;
    int * array;
    
    argc = 2;
    // argv[1] = "2623 1363 1960 4313 1800 2337 2450 2675 475 542 1659 316 3132 998 4295 1215 4135 4644 474 1248 4895 897 2821 3706 3648 1288 1250 4521 341 2873 1333 2254 3643 3871 4177 3115 661 4946 1201 945 4844 3891 1294 3158 3442 2210 537 796 1051 3084";
    // argv[1] = "3173 2068 4853 4935 1257 4198 4945 2383 4363 2140 550 2170 682 2137 3586";
    // argv[1] = "4499 813 4133 3119 3397 140 4759 3676 3300 1551";
    // argv[1] = "2024 2492 4645 2514 4107 1871 1907 2586 789 1399";
    argv[1] = "347 2770 3130 4420 2436 1600 2415 3690 1932 1589 3704 3217 2700 2854 4898 2442 3765 1886 126 1009 1400 1958 3063 445 4321 1125 3757 2733 1161 1121 3421 4585 2750 609 4869 4713 213 960 3798 1393 3864 2852 3114 3981 3160 2689 165 636 3243 4261 2648 2940 3248 304 3370 4557 744 699 3144 4689 2553 2551 2187 1601 3127 1544 1362 2075 3814 4721 133 2999 3230 3594 3394 4252 4575 1769 3330 466 4266 808 548 1445 2407 4671 4229 3250 1933 4487 3937 3770 1722 4194 4901 1621 2546 4311 4065 1043";
    // argv[1] = "31 129 67 55 576 308 71";
    // argv [1] = "1974 200 2064 1283 3655 727 314 1899 1115 375 2095 1348 4806 789 452 3288 1775 3784 819 3973 513 3385 4921 2966 3979 2862 2015 4625 4756 3278";
    // argv[1] = "12 475 562 22 397 285 135 215 56 603 432 100 293";
    // argv[1] = "627 533 574 438 174 582 591 310 4 367 89 494 275 15 445 434 142 362 640 408";
    char * s = "----------------------------\n";

    cdl_list.a = malloc(sizeof(*cdl_list.a));
    cdl_list.b = malloc(sizeof(*cdl_list.b));
    rank_.a = malloc(sizeof(*rank_.a));
    rank_.b = malloc(sizeof(*rank_.b));

    cdl_init_list(cdl_list.a);
    cdl_init_list(cdl_list.b);
    cdl_init_list(rank_.a);
    cdl_init_list(rank_.b);

    cdl_init_list(&ops);

    if (argc > 1 && parse_input(argc, argv, cdl_list.a))
    {
        // ft_printf("%sInput\n%s", s, s);
        // print_cdl(cdl_list.a);

        rank(cdl_list.a, rank_.a);

        // print_cdl(rank_.a);

        array = lis(cdl_list.a);
        // print_array(array, cdl_list_a.total);

        deal(&cdl_list, &rank_, array, &ops);
        // print_cdl(rank_.a);
        // print_cdl(rank_.b);
        sort(&cdl_list, &rank_, &ops);
        cdl_free_list(rank_.a);
        rank(cdl_list.a, rank_.a);
        // print_cdl(rank_.a);
        reorder(cdl_list.a, rank_.a, &ops);
        cdl_free_list(rank_.a);
        rank(cdl_list.a, rank_.a);
        // print_cdl(rank_.a);
        // print_cdl_str(&ops);
        optimize_ops_r(&ops);
        optimize_ops_rr(&ops);
        
        // ft_printf("\nopti\n\n\n");
        print_cdl_str(&ops);
        free(array);
        cdl_free_list(&ops);
        cdl_free_list(rank_.a);
        cdl_free_list(cdl_list.a);
        cdl_free_list(cdl_list.b);
        cdl_free_list(rank_.b);
    }
    else
        return (free(cdl_list.a),free(cdl_list.b),free(rank_.a),free(rank_.b),ERROR);
    return (free(cdl_list.a),free(cdl_list.b),free(rank_.a),free(rank_.b),SUCCESS);
}

