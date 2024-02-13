/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:51:24 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/13 10:04:55 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int parse_input(int argc, char ** argv, t_circular_double_link_list * cdl_list)
{
    int status;

    status = ERROR;
    if (argc == 2)
    {
        status = parse_string(argv[1], cdl_list, &status);
        if (status == ERROR)
            return(ft_printf("Error\n"), ERROR);
    }
    else if (argc > 2)
    {
        status = parse_arguments(argc, argv, cdl_list, &status);
        if (status == ERROR)
            return(ft_printf("Error\n"), ERROR);
    }
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
    if (!inputs || inputs[i] == NULL)
        return (free(inputs), ERROR);
    while(inputs[i])
    {
        value = ft_atoi_safe(inputs[i], status);
        if (!(*status == SUCCESS && add_int2node(cdl_list, cdl_node, value)))
            return (free_split(inputs), cdl_free_list(cdl_list), ERROR);
        i++;
    }
    if (check_duplicate(cdl_list) == ERROR)
        return (free_split(inputs), cdl_free_list(cdl_list), ERROR);
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
    if (check_duplicate(cdl_list) == ERROR)
        return (cdl_free_list(cdl_list), ERROR);
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

int * cdl2array(t_circular_double_link_list * cdl_list)
{
    t_double_link_node * cdl_node;
    size_t i;
    int * array;

    i = 0;
    array = malloc(sizeof(*array) * cdl_list->total);
    cdl_node = cdl_list->first_node;
    if (array && cdl_list->first_node)
    {
        do {
            array[i] = *((int *)cdl_node->data);
            cdl_node = cdl_node->next;
            ++i;
        } while (cdl_node != cdl_list->first_node);
    }
    return (array);
}
