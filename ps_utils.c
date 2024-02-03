/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:51:24 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/03 16:35:44 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/mylibc/mylibc_local.h"
#include "push_swap.h"

int parse_input(int argc, char ** argv, t_circular_double_link_list * cdl_list)
{
    int status;
    t_double_link_node * cdl_node;

    status = ERROR;
    if (argc == 2)
    {
        status = parse_string(argv[1], cdl_list, &status);
        if (status == ERROR)
            ft_printf("Error\n");
    }
    else if (argc > 2)
    {
        status = parse_arguments(argc, argv, cdl_list, &status);
        if (status == ERROR)
            ft_printf("Error\n");
    }
    if (status)
    {
        cdl_node = cdl_list->first_node;
        do {
            ft_printf("%d\n", *((int *)cdl_node->data));
            cdl_node = cdl_node->next;
        } while (cdl_node != cdl_list->first_node);
    }
    else
        return (ERROR);
    return (SUCCESS);
}

int parse_string(char * string, t_circular_double_link_list * cdl_list, int * status)
{
    char ** inputs;
    int value;
    size_t i;
    t_double_link_node * cdl_node;

    i = 0;
    inputs = ft_split(string, ' ');
    if (!inputs)
        return (ERROR);
    while(inputs[i])
    {
        value = ft_atoi_safe(inputs[i], status);
        if (!(*status == SUCCESS && add_int2node(cdl_list, cdl_node, value)))
            return (free_split(inputs), cdl_free_list(cdl_list), ERROR);
        i++;
    }
    return (free_split(inputs), SUCCESS);
}

int parse_arguments(int argc, char ** argv, t_circular_double_link_list * cdl_list, int * status)
{
    int value;
    size_t i;
    t_double_link_node * cdl_node;

    i = 1;
    while(i < argc)
    {
        value = ft_atoi_safe(argv[i], status);
        if (!(*status == SUCCESS && add_int2node(cdl_list, cdl_node, value)))
            return (cdl_free_list(cdl_list), ERROR);
        i++;
    }
    return (SUCCESS);
}

int add_int2node(t_circular_double_link_list * cdl_list, t_double_link_node * cdl_node, int value)
{
    cdl_node = malloc(sizeof(*cdl_node)); 

    if (cdl_node && cdl_list->pf_insert_end(cdl_list, cdl_node))
    {
        cdl_node->data = malloc(sizeof(value));;
        if (!cdl_node->data)
            return (ERROR);
        *((int *)cdl_node->data) = value;
    }
    else
        return (ERROR);

    return (SUCCESS);
}
