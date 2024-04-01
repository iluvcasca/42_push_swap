/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 20:01:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 15:17:39 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_fast_sort(t_vars *vars, t_circular_db_ll **rank_cpy,
		int **array)
{
	*rank_cpy = malloc(sizeof(**rank_cpy));
	cdl_init_list(*rank_cpy);
	rank(vars->cdl_list_a, *rank_cpy);
	*array = cdl2array(*rank_cpy);
}

static void	swap_both(t_vars *vars)
{
	swap(vars->cdl_list_a, 'a', vars->ops);
	swap(vars->rank_a, 0, vars->ops);
}

static void	rotate_both(t_vars *vars)
{
	rotate(vars->cdl_list_a, 'a', vars->ops);
	rotate(vars->rank_a, 0, vars->ops);
}

static void	r_rotate_both(t_vars *vars)
{
	r_rotate(vars->cdl_list_a, 'a', vars->ops);
	r_rotate(vars->rank_a, 0, vars->ops);
}

int	fast_sort(t_vars *vars)
{
	int					*array;
	t_circular_db_ll	*rank_cpy;

	init_fast_sort(vars, &rank_cpy, &array);
	if (array[0] == 1 && array[1] == 0 && array[2] == 2)
		swap_both(vars);
	else if (array[0] == 0 && array[1] == 2 && array[2] == 1)
	{
		rotate_both(vars);
		swap_both(vars);
		r_rotate_both(vars);
	}
	else if (array[0] == 2 && array[1] == 1 && array[2] == 0)
	{
		swap_both(vars);
		r_rotate_both(vars);
	}
	else if (array[0] == 1 && array[1] == 2 && array[2] == 0)
		r_rotate_both(vars);
	else if (array[0] == 2 && array[1] == 0 && array[2] == 1)
		rotate_both(vars);
	return (free(array), cdl_free_list(rank_cpy), free(rank_cpy), SUCCESS);
}
