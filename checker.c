/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:58:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/12 22:22:59 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdlib.h"

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

void free_all(t_vars * vars)
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

size_t ops_len(char * line)
{
    size_t i;

    i = 0;
    while (line[i] != '\n')
        ++i;
    return i;
}

int process(char * line, t_vars * vars)
{
    size_t n;

    n = ft_strlen(line);
    if (!ft_strncmp(line, "sa\n", n))
       swap(vars->cdl_list_a, 0, vars->ops);
    else if (!ft_strncmp(line, "sb\n", n))
       swap(vars->cdl_list_b, 0, vars->ops);
    else if (!ft_strncmp(line, "ss\n", n))
    {
       swap(vars->cdl_list_a, 0, vars->ops);
       swap(vars->cdl_list_b, 0, vars->ops);
    }
    else if (!ft_strncmp(line, "pa\n", n))
        push(vars->cdl_list_a, vars->cdl_list_b, 0, vars->ops);
    else if (!ft_strncmp(line, "pb\n", n))
        push(vars->cdl_list_b, vars->cdl_list_a, 0, vars->ops);
    else if (!ft_strncmp(line, "ra\n", n))
        rotate(vars->cdl_list_a, 0, vars->ops);
    else if (!ft_strncmp(line, "rb\n", n))
        rotate(vars->cdl_list_b, 0, vars->ops);
    else if (!ft_strncmp(line, "rra\n", n))
        r_rotate(vars->cdl_list_a, 0, vars->ops);
    else if (!ft_strncmp(line, "rrb\n", n))
        r_rotate(vars->cdl_list_b, 0, vars->ops);
    else if (!ft_strncmp(line, "rr\n", n))
    {
        rotate(vars->cdl_list_a, 0, vars->ops);
        rotate(vars->cdl_list_b, 0, vars->ops);
    }
    else if (!ft_strncmp(line, "rrr\n", n))
    {
        r_rotate(vars->cdl_list_a, 0, vars->ops);
        r_rotate(vars->cdl_list_b, 0, vars->ops);
    }
    else 
        return (ERROR);
    return (SUCCESS);
}

int apply_ops(t_vars * vars)
{
    char * line;

    while (1)
    {
        line = get_next_line(0);
        if (!line)
            break;
        if (!process(line, vars))
            return (free(line),free_all(vars),ft_printf("Error\n"),ERROR);
        free(line);
    }
    rank(vars->cdl_list_a, vars->rank_a);
    if (check_sorted(vars)) 
        ft_printf("KO\n");
    else
        ft_printf("OK\n");
    return (free_all(vars),SUCCESS);
}

int main(int argc, char ** argv)
{
    t_vars * vars;
    int status;

    // argc = 2;
    // argv[1] = "2005 1586 2393 1242 4006 3197 724 40 3370 221 1693 4738 2015 2354 1911 553 4676 1132 253 4312 1654 1993 2224 653 3583 688 157 2504 479 2430 210 3714 2925 2381 187 2218 4741 4919 2656 519";
    vars = malloc(sizeof(*vars));
    vars->array = malloc(sizeof(int));
    if (!vars)
        return ERROR;
    init(vars); 
    if (argc > 1)
        status = parse_input(argc, argv, vars->cdl_list_a); 
    else
        return (free_all(vars),ERROR);
    if (status)
        apply_ops(vars);
    else 
        free_all(vars);
    return (SUCCESS);
}
