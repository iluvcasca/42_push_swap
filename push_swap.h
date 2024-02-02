/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:50:43 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/02 18:43:27 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

#include "libft/mylibc.h"

int parse_input(int argc, char ** argv, t_circular_double_link_list * cdl_list);
int parse_string(char * string, t_circular_double_link_list * cdl_list, int * status);
int parse_arguments(int argc, char ** argv, t_circular_double_link_list * cdl_list, int * status);
int add_int2node(t_circular_double_link_list * cdl_list, t_double_link_node * cdl_node, int value);
#endif
