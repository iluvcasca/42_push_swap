/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:51:24 by kgriset           #+#    #+#             */
/*   Updated: 2024/03/11 19:20:53 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/mylibc/mylibc_local.h"
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
    t_parse_string vars;
    char ** inputs;
    size_t i;
    t_double_link_node * cdl_node;

    i = 0;
    inputs = ft_split(string, ' ');
    if (!inputs || inputs[i] == NULL)
        return (free(inputs), ERROR);
    while(inputs[i])
    {
        vars.temp = ft_strtrim(inputs[i], "+");
        vars.value = ft_atoi_safe(vars.temp, status);
        if (!(*status == SUCCESS && add_int2node(cdl_list, cdl_node, vars.value)))
            return (free(vars.temp),free_split(inputs), cdl_free_list(cdl_list), ERROR);
        free(vars.temp);
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
    char * temp;

    i = 1;
    while(i < argc)
    {
        temp = ft_strtrim(argv[i]," +");
        value = ft_atoi_safe(temp, status);
        if (!(*status == SUCCESS && add_int2node(cdl_list, cdl_node, value) && argv[i][0]))
            return (free(temp),cdl_free_list(cdl_list), ERROR);
        free(temp);
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
