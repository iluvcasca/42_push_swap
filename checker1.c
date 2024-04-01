/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:18:50 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 15:20:42 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	process1(char *line, t_vars *vars, size_t n)
{
	if (!ft_strncmp(line, "rrb\n", n))
		return (r_rotate(vars->cdl_list_b, 0, vars->ops), SUCCESS);
	else if (!ft_strncmp(line, "rr\n", n))
	{
		rotate(vars->cdl_list_a, 0, vars->ops);
		rotate(vars->cdl_list_b, 0, vars->ops);
		return (SUCCESS);
	}
	else if (!ft_strncmp(line, "rrr\n", n))
	{
		r_rotate(vars->cdl_list_a, 0, vars->ops);
		r_rotate(vars->cdl_list_b, 0, vars->ops);
		return (SUCCESS);
	}
	return (ERROR);
}

int	process(char *line, t_vars *vars)
{
	size_t	n;

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
	else if (!process1(line, vars, n))
		return (ERROR);
	return (SUCCESS);
}
