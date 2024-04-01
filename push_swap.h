/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:50:43 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 13:10:44 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

#include "libft/mylibc.h"

typedef struct s_vars {
    t_circular_db_ll * cdl_list_a;
    t_circular_db_ll * cdl_list_b;
    t_circular_db_ll * rank_a;
    t_circular_db_ll * rank_b;
    t_circular_db_ll * ops;
    int * array;
} t_vars;

typedef struct s_parse_string {
    int value;
    char * temp;
} t_parse_string;

typedef struct s_lis_vars {
    int * lis ;
    int * cdl_array;
    int * lis_count;
    int i ;
    size_t j;
    size_t lis_max;
    size_t lis_max_index;
} t_lis_vars;

typedef struct s_mov_vars {
    size_t i;
    size_t j;
    size_t sum_current;
    size_t sum;
    int * array_b;
    int * mov_b;
    int * array_a;
    int * mov_a;
    int insert;
} t_mov_vars;

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

//utils 
void print_array(int * array, size_t size);
void print_cdl(t_circular_db_ll * cdl_list);
void print_cdl_str(t_circular_db_ll * cdl_list);
int check_sorted(t_vars * vars);
void free_all(t_vars * vars);

// parsing
int parse_input(int argc, char ** argv, t_circular_db_ll * cdl_list);
int parse_string(char * string, t_circular_db_ll * cdl_list, int * status);
int parse_arguments(int argc, char ** argv, t_circular_db_ll * cdl_list, int * status);
int add_int2node(t_circular_db_ll * cdl_list, t_double_link_node * cdl_node, int value);
int * cdl2array(t_circular_db_ll * cdl_list);
int check_duplicate(t_circular_db_ll * cdl_list);

// operations
int swap(t_circular_db_ll * cdl_list, char list_name, t_circular_db_ll * ops);
int ss(t_circular_db_ll * cdll_a, t_circular_db_ll * cdll_b, t_circular_db_ll * ops);
int push(t_circular_db_ll * cdll_a, t_circular_db_ll * cdll_b, char list_name, t_circular_db_ll * ops);
int rotate(t_circular_db_ll * cdl_list, char list_name, t_circular_db_ll * ops);
int rr(t_circular_db_ll * cdll_a, t_circular_db_ll * cdll_b, t_circular_db_ll * ops);
int r_rotate(t_circular_db_ll * cdl_list, char list_name, t_circular_db_ll * ops);
int r_rr(t_circular_db_ll * cdll_a, t_circular_db_ll * cdll_b, t_circular_db_ll * ops);

void push_n(t_circular_db_ll * cdll_a, t_circular_db_ll * cdll_b, char list_name, size_t n, t_circular_db_ll * ops);
void r_rotate_n(t_circular_db_ll * cdl_list, char list_name, size_t n, t_circular_db_ll * ops);
void rotate_n(t_circular_db_ll * cdl_list, char list_name, size_t n, t_circular_db_ll * ops);

// sorting
size_t min_size_t(size_t a, size_t b);
int * bottom_up_merge_sort(int * array, size_t n);
void bottom_up_merge(int * A, t_i _i, int * B);
void update_merge(size_t * width, int ** array, int ** array_cpy);

// algo
int rank(t_circular_db_ll * cdll, t_circular_db_ll * rank);
int * lis(t_circular_db_ll * cdll_a);
int deal(t_vars * vars);
size_t max_size(size_t a, size_t b);
void sort(t_vars * vars);
int * compute_mov(t_vars * vars);
void reorder(t_circular_db_ll * cdll_a, t_circular_db_ll * rank_a, t_circular_db_ll * ops);
int abs(int a);

void count_ops_r(t_circular_db_ll * cdl_list, t_double_link_node ** node, size_t * count, char ops);
void insert_rr(t_circular_db_ll * cdl_list, t_double_link_node * node);
int optimize_ops_r(t_circular_db_ll * cdl_list);
void process_ops_r(t_circular_db_ll * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node);
void insert_while_rr(t_circular_db_ll * cdl_list, t_double_link_node * cdl_node, size_t * count_rr);
void del_r(t_circular_db_ll * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, size_t * count_rr);
void iter_ops_rb(t_circular_db_ll * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node);
void iter_ops_ra(t_circular_db_ll * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node);

void count_ops_rr(t_circular_db_ll * cdl_list, t_double_link_node ** node, size_t * count, char ops);
void insert_rrr(t_circular_db_ll * cdl_list, t_double_link_node * node);
int optimize_ops_rr(t_circular_db_ll * cdl_list);
void process_ops_rr(t_circular_db_ll * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node);
void iter_ops_rrb(t_circular_db_ll * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node);
void iter_ops_rra(t_circular_db_ll * cdl_list, t_double_link_node ** cdl_node_r, size_t * count_r, t_double_link_node ** cdl_node);
void insert_while_rrr(t_circular_db_ll * cdl_list, t_double_link_node * cdl_node, size_t * count_rr);

int fast_sort(t_vars * vars);
int sort_small(t_vars * vars);
#endif
