/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:51:24 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/01 15:29:57 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/mylibc/mylibc_local.h"
#include "push_swap.h"

int parse_input(int argc, char ** argv, t_circular_double_link_list * cdl_list)
{
    int status;
    char ** inputs;
    int temp_int;
    size_t i;
    t_double_link_node * cdl_node;

    status = SUCCESS;
    inputs = NULL;
    temp_int = 0;
    i = 0;
    cdl_init_list(cdl_list);
    if (argc == 2)
    {
        inputs = ft_split(argv[1], ' ');
        while(inputs[i])
        {
            temp_int = ft_atoi_safe(inputs[i], &status);
            if (status)
            {
                cdl_node = malloc(sizeof(*cdl_node)); 
                if (cdl_node && cdl_list->pf_insert_end(cdl_list, cdl_node))
                {
                    cdl_node->data = malloc(sizeof(temp_int));;
                    *((int *)cdl_node->data) = temp_int;
                }
            }
            else 
                return (status);
            i++;
        }
    }
    cdl_node = cdl_list->first_node;
    do {
        ft_printf("%d\n", *((int *)cdl_node->data));
        cdl_node = cdl_node->next;
    } while (cdl_node != cdl_list->first_node);
    return (status);
}
