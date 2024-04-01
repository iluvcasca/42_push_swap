/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:58:49 by kgriset           #+#    #+#             */
/*   Updated: 2024/04/01 15:23:34 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	init(t_vars *vars)
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

void	free_all(t_vars *vars)
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

size_t	ops_len(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\n')
		++i;
	return (i);
}

int	apply_ops(t_vars *vars)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (!process(line, vars))
			return (free(line), free_all(vars), ft_printf("Error\n"), ERROR);
		free(line);
	}
	rank(vars->cdl_list_a, vars->rank_a);
	if (check_sorted(vars))
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	return (free_all(vars), SUCCESS);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	int		status;

	vars = malloc(sizeof(*vars));
	vars->array = malloc(sizeof(int));
	if (!vars)
		return (ERROR);
	init(vars);
	if (argc > 1)
		status = parse_input(argc, argv, vars->cdl_list_a);
	else
		return (free_all(vars), ERROR);
	if (status)
		apply_ops(vars);
	else
		free_all(vars);
	return (SUCCESS);
}
