/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_lis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:05:03 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 15:16:30 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static void	init_lis(t_lis_vars *vars, t_circular_db_ll *cdll_a)
{
	vars->cdl_array = cdl2array(cdll_a);
	vars->lis_count = malloc(sizeof(int) * cdll_a->total);
	vars->i = 0;
	vars->j = 0;
	vars->lis_max = 1;
	vars->lis_max_index = 0;
}

static void	lis2(t_lis_vars *vars, t_circular_db_ll *cdll_a, int *lis)
{
	vars->i = 0;
	while ((size_t)vars->i < cdll_a->total)
	{
		if (vars->lis_max < (size_t)vars->lis_count[vars->i])
		{
			vars->lis_max = vars->lis_count[vars->i];
			vars->lis_max_index = vars->i;
		}
		++(vars->i);
	}
	vars->i = vars->lis_max_index;
	vars->j = vars->lis_max - 1;
	lis[(vars->j)--] = vars->cdl_array[vars->i];
	while (vars->i >= 0)
	{
		if ((size_t)vars->lis_count[vars->i] == vars->lis_max - 1)
		{
			lis[vars->j] = vars->cdl_array[vars->i];
			vars->lis_max = vars->lis_count[vars->i];
			--(vars->j);
		}
		--(vars->i);
	}
}

int	*lis(t_circular_db_ll *cdll_a)
{
	t_lis_vars	*vars;
	int			*lis;

	lis = malloc(sizeof(*lis) * cdll_a->total);
	vars = malloc(sizeof(*vars));
	init_lis(vars, cdll_a);
	ft_memset(lis, 0, sizeof(*lis) * cdll_a->total);
	while ((size_t)vars->i < cdll_a->total)
	{
		vars->lis_count[vars->i] = 1;
		vars->j = 0;
		while (vars->j < (size_t)vars->i)
		{
			if (vars->cdl_array[vars->i] > vars->cdl_array[vars->j]
				&& vars->lis_count[vars->i] < vars->lis_count[vars->j] + 1)
				vars->lis_count[vars->i] = vars->lis_count[vars->j] + 1;
			++(vars->j);
		}
		++(vars->i);
	}
	lis2(vars, cdll_a, lis);
	return (free(vars->lis_count), free(vars->cdl_array), free(vars), lis);
}
