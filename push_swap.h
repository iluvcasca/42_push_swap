/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:50:43 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/08 15:38:50 by kgriset          ###   ########.fr       */
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

typedef struct s_cdl_i {
    size_t bottom;
    size_t left;
    size_t right;
    size_t end;
    size_t * run_left;
    size_t * run_right;

} t_cdl_i;

typedef struct s_run {
    int * map;
    size_t map_size;
    size_t run_nb;
} t_run;

//temp 
void print_array(int * array, size_t size);
void print_cdl(t_circular_double_link_list * cdl_list);
// parsing
int parse_input(int argc, char ** argv, t_circular_double_link_list * cdl_list);
int parse_string(char * string, t_circular_double_link_list * cdl_list, int * status);
int parse_arguments(int argc, char ** argv, t_circular_double_link_list * cdl_list, int * status);
int add_int2node(t_circular_double_link_list * cdl_list, t_double_link_node * cdl_node, int value);
int * cdl2array(t_circular_double_link_list * cdl_list);
int check_duplicate(t_circular_double_link_list * cdl_list);

// operations
int swap(t_circular_double_link_list * cdl_list, char list_name);
void ss(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b);
int push(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b, char list_name);
int rotate(t_circular_double_link_list * cdl_list, char list_name);
void rr(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b);
int r_rotate(t_circular_double_link_list * cdl_list, char list_name);
void r_rr(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b);

void push_n(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b, char list_name, size_t n);
void r_rotate_n(t_circular_double_link_list * cdl_list, char list_name, size_t n);
void rotate_n(t_circular_double_link_list * cdl_list, char list_name, size_t n);

// sorting
size_t min_size_t(size_t a, size_t b);
int * bottom_up_merge_sort(int * array, size_t n);
void bottom_up_merge(int * A, t_i _i, int * B);
void update_merge(size_t * width, int ** array, int ** array_cpy);

// algo
int cdl_bottom_up_merge_sort(t_circular_double_link_list * cdll_a,t_circular_double_link_list * cdll_b);
void deal(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b);
int set_run(t_circular_double_link_list * cdll_a, t_run * run_a, t_circular_double_link_list * cdll_b, t_run * run_b);
void print_map(t_run * run);
#endif
