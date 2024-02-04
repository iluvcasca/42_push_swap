/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:50:43 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/04 17:24:34 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

#include "libft/mylibc.h"

typedef struct s_i {
    size_t left;
    size_t right;
    size_t end;
} t_i;

// parsing
int parse_input(int argc, char ** argv, t_circular_double_link_list * cdl_list);
int parse_string(char * string, t_circular_double_link_list * cdl_list, int * status);
int parse_arguments(int argc, char ** argv, t_circular_double_link_list * cdl_list, int * status);
int add_int2node(t_circular_double_link_list * cdl_list, t_double_link_node * cdl_node, int value);
int * cdl2array(t_circular_double_link_list * cdl_list);
int check_duplicate(t_circular_double_link_list * cdl_list);

// sorting
size_t min_size_t(size_t a, size_t b);
int * bottom_up_merge_sort(int * array, size_t n);
void bottom_up_merge(int * A, t_i _i, int * B);
void update_merge(size_t * width, int ** array, int ** array_cpy);
#endif
