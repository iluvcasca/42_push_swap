/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/11 18:57:28 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void init_mov(t_vars * vars, t_mov_vars * mov_vars)
{
    mov_vars->insert = max_size(vars->cdl_list_a->total, 
                                vars->cdl_list_b->total);
    mov_vars->mov_b = cdl2array(vars->cdl_list_b);
    mov_vars->array_b = cdl2array(vars->rank_b);
    mov_vars->mov_a = cdl2array(vars->cdl_list_a);
    mov_vars->array_a = cdl2array(vars->rank_a);
    mov_vars->i = 0;
}

static void compute_mov1(t_vars * vars, t_mov_vars * mov_vars)
{
    while(mov_vars->i < vars->cdl_list_b->total)
    {
        if (mov_vars->i <= vars->cdl_list_b->total / 2)
            mov_vars->mov_b[mov_vars->i] = mov_vars->i;
        else
            mov_vars->mov_b[mov_vars->i] = mov_vars->i - 
                (vars->cdl_list_b->total);
        ++(mov_vars->i);
    }
    mov_vars->i = 0;
    while(mov_vars->i < vars->cdl_list_a->total)
    {
        if (mov_vars->i <= vars->cdl_list_a->total / 2)
            mov_vars->mov_a[mov_vars->i] = mov_vars->i;
        else
            mov_vars->mov_a[mov_vars->i] = mov_vars->i - 
                (vars->cdl_list_a->total);
        ++(mov_vars->i);
    }
    mov_vars->i = 0; 
    mov_vars->sum_current = max_size(vars->cdl_list_b->total, 
                                     vars->cdl_list_a->total);
}

static void compute_mov2(t_vars * vars, t_mov_vars * mov_vars)
{
    mov_vars->insert = max_size(vars->cdl_list_a->total, 
                                vars->cdl_list_b->total);
    mov_vars->j = 0;
    while (mov_vars->j < vars->cdl_list_a->total)
    {
        if (abs(mov_vars->array_a[mov_vars->j] - 
                mov_vars->array_b[mov_vars->i]) <= mov_vars->insert)
            mov_vars->insert = abs(mov_vars->array_a[mov_vars->j] 
                                   - mov_vars->array_b[mov_vars->i]);
        ++(mov_vars->j);
    }
    mov_vars->j = 0;
    while (mov_vars->j < vars->cdl_list_a->total 
        && abs(mov_vars->array_a[mov_vars->j] - 
               mov_vars->array_b[mov_vars->i]) != mov_vars->insert)
        ++(mov_vars->j);
    if (mov_vars->array_a[mov_vars->j] - mov_vars->array_b[mov_vars->i] 
        < 0 && mov_vars->j + 1 < vars->cdl_list_a->total)
        ++(mov_vars->j);
    else if (mov_vars->array_a[mov_vars->j] - 
            mov_vars->array_b[mov_vars->i] < 0 && mov_vars->j + 1 
            == vars->cdl_list_a->total)
        mov_vars->j = 0;
}

static void compute_mov3(t_vars * vars, t_mov_vars * mov_vars, int * mov)
{
    if (mov_vars->mov_a[mov_vars->j] < 0 
        && mov_vars->mov_b[mov_vars->i] < 0)
        mov_vars->sum = max_size((size_t){mov_vars->mov_a[mov_vars->j]*-1},
                                 (size_t){mov_vars->mov_b[
                                 mov_vars->i]*-1}); 
    else if (mov_vars->mov_a[mov_vars->j] >= 0 
            && mov_vars->mov_b[mov_vars->i] < 0)
        mov_vars->sum = mov_vars->mov_a[mov_vars->j] 
            + mov_vars->mov_b[mov_vars->i]*-1;
    else if (mov_vars->mov_a[mov_vars->j] < 0 
            && mov_vars->mov_b[mov_vars->i] >= 0)
        mov_vars->sum = mov_vars->mov_b[mov_vars->i] 
            + mov_vars->mov_a[mov_vars->j]*-1;
    else
        mov_vars->sum = max_size((size_t)mov_vars->mov_a[
                                 mov_vars->j],(size_t)mov_vars->mov_b[
                                 mov_vars->i]);
    if (mov_vars->sum < mov_vars->sum_current)
    {
        mov_vars->sum_current = mov_vars->sum;
        mov[0] = mov_vars->mov_a[mov_vars->j]; 
        mov[1] = mov_vars->mov_b[mov_vars->i]; 
    }
}

int * compute_mov(t_vars * vars)
{
    t_mov_vars * mov_vars;
    int * mov;
    
    mov_vars = malloc(sizeof(*mov_vars));
    mov = malloc(sizeof(*mov) * 2);
    init_mov(vars, mov_vars);    
    compute_mov1(vars, mov_vars);
    while (mov_vars->i < vars->cdl_list_b->total)
    {
        compute_mov2(vars, mov_vars);
        compute_mov3(vars, mov_vars, mov);
        ++(mov_vars->i); 
    }
    return (free(mov_vars->array_a), free(mov_vars->array_b), 
    free(mov_vars->mov_a), free(mov_vars->mov_b), free(mov_vars), mov);
}
