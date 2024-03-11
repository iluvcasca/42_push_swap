/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:36:26 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/11 16:37:53 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void init(t_vars *vars)
{
    vars->rank_a = malloc(sizeof(*(vars->rank_a)));
    vars->rank_b = malloc(sizeof(*(vars->rank_b)));
    vars->ops = malloc(sizeof(*(vars->ops)));
    vars->cdl_list_a = malloc(sizeof(*(vars->cdl_list_a)));
    vars->cdl_list_b = malloc(sizeof(*(vars->cdl_list_b)));

    cdl_init_list(vars->cdl_list_a);
    cdl_init_list(vars->cdl_list_b);
    cdl_init_list(vars->rank_a);
    cdl_init_list(vars->rank_b);
    cdl_init_list(vars->ops);
}

static void free_all(t_vars * vars)
{
    free(vars->array);
    cdl_free_list(vars->ops);
    cdl_free_list(vars->rank_a);
    cdl_free_list(vars->cdl_list_a);
    cdl_free_list(vars->cdl_list_b);
    cdl_free_list(vars->rank_b);

    free(vars->rank_a);
    free(vars->rank_b);
    free(vars->cdl_list_a);
    free(vars->cdl_list_b);
    free(vars->ops);
    free(vars);
}

static void sort_all(t_vars * vars)
{
    rank(vars->cdl_list_a, vars->rank_a);
    vars->array = lis(vars->cdl_list_a);
    deal(vars);
    sort(vars);
    cdl_free_list(vars->rank_a);
    rank(vars->cdl_list_a, vars->rank_a);
    reorder(vars->cdl_list_a, vars->rank_a, vars->ops);
    cdl_free_list(vars->rank_a);
    rank(vars->cdl_list_a, vars->rank_a);
    optimize_ops_r(vars->ops);
    optimize_ops_rr(vars->ops);
    print_cdl_str(vars->ops);
}

int main(int argc, char ** argv)
{
    t_vars * vars;
    int status;

    vars = malloc(sizeof(*vars));
    if (!vars)
        return ERROR;
    init(vars); 
    if (argc > 1)
        status = parse_input(argc, argv, vars->cdl_list_a); 
    else
        return (ERROR);
    if (status)
        sort_all(vars);
    return (free_all(vars), SUCCESS);
}
