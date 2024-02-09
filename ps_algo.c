/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgriset <kgriset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:40:32 by kgriset           #+#    #+#             */
/*   Updated: 2024/02/09 10:44:07 by kgriset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void deal(t_circular_double_link_list * cdll_a, t_circular_double_link_list * cdll_b)
{
    size_t n;
    size_t j = 0;
    int * array;

    n = cdll_a->total;
    array = cdl2array(cdll_a);
    if (!array)
        return;
    while (j + 1 < n)
    {
        if (array[j] < array[j+1])
        {
            rotate(cdll_a, 'a');
            rotate(cdll_a, 'a');
        }
        else
    {
            push(cdll_b, cdll_a, 'b');
            push(cdll_b, cdll_a, 'b');
        }
        j+=2;
    }
    while (cdll_a->total > cdll_b->total)
    {
        swap(cdll_a, 'a');
        push(cdll_b, cdll_a, 'b');
        push(cdll_b, cdll_a, 'b');
    }
    while (cdll_a->total < cdll_b->total)
    {
        swap(cdll_b, 'b');
        push(cdll_a, cdll_b, 'a');
        push(cdll_a, cdll_b, 'a');
    }
    free(array);
}

void deal2(t_circular_double_link_list * cdll, t_run * run, char list_name)
{
    int * array;
    size_t i;

    i = 0;

    while (i < run->map_size)
    {
        array = cdl2array(cdll); 
        set_run(cdll, run);
        if (!run->map ||!array )
            return (free(array), free(run->map));
        array_in_place_reverse(run->map, run->map_size); 

        if (run->map[0] == 'x' && run->map[1] == 'x')
        {
            swap(cdll, list_name);  
            rotate_n(cdll, list_name, 2);
            i+=2;
            print_cdl(cdll);
        }
        else if (run->map[0] == 'x' && run->map[run->map_size-1] == 'x')
        {
            r_rotate(cdll, list_name);
            swap(cdll, list_name);  
            rotate_n(cdll, list_name, 2);
            i+=2;
            print_cdl(cdll);
        }
        else if (run->map[0] == 'e' && run->map[1] == 's' && run->map[3] == 's' && array[1] <= array[3])
        {
            rotate(cdll, list_name); 
            swap(cdll, list_name);
            r_rotate(cdll, list_name);
            if (array[0] > array[2])
                swap(cdll, list_name);
            rotate(cdll, list_name);
            rotate_n(cdll, list_name, 3);
            i+=4;
            print_cdl(cdll);
        }
        else if (run->map[0] == 'e' && run->map[1] == 's' && run->map[3] == 's' && array[1] > array[3])
        {
            rotate(cdll, list_name); 
            swap(cdll, list_name);
            r_rotate(cdll, list_name);
            if (array[0] > array[2])
                swap(cdll, list_name);
            rotate(cdll, list_name);
            rotate(cdll, list_name);
            swap(cdll, list_name);
            rotate_n(cdll, list_name, 2);
            i+=4;
            print_cdl(cdll);
        }
        else if (run->map[0] == 'e' && run->map[1] == 's' 
            && run->map[run->map_size - 1] == 's' && run->map[run->map_size - 2] == 'e' && array[run->map_size - 1] <= array[1])
        {
            r_rotate(cdll, list_name); 
            swap(cdll, list_name);
            r_rotate(cdll, list_name);
            if (array[run->map_size - 2] > array[0])
                swap(cdll, list_name);
            rotate(cdll, list_name);
            rotate_n(cdll, list_name, 3);
            i+=2;
            print_cdl(cdll);
        }
        else if (run->map[0] == 'e' && run->map[1] == 's' 
            && run->map[run->map_size - 1] == 's' && run->map[run->map_size - 2] == 'e' && array[run->map_size - 1] > array[1])
        {
            r_rotate(cdll, list_name); 
            swap(cdll, list_name);
            r_rotate(cdll, list_name);
            if (array[run->map_size - 2] > array[0])
                swap(cdll, list_name);
            rotate(cdll, list_name);
            rotate(cdll, list_name);
            swap(cdll, list_name);
            rotate_n(cdll, list_name, 2);
            i+=2;
            print_cdl(cdll);
        }
        else
        {
            break;
        }
        free(array);
        free(run->map);
    }
    if (i != run->map_size)
    {
        free(array);
        free(run->map);
    }
}

int set_run(t_circular_double_link_list * cdll_a, t_run * run_a)
{
    int * array_a;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    run_a->map = malloc(sizeof(int)*cdll_a->total);
    run_a->map_size = cdll_a->total;
    run_a->run_nb = 0;

    array_a = cdl2array(cdll_a); 
    if (!run_a->map || !array_a)
        return (free(run_a->map),free(array_a), ERROR);
    array_in_place_reverse(array_a, cdll_a->total);

    while (i < run_a->map_size)
    {
        j = i;
        while (j + 1 < run_a->map_size && array_a[j] >= array_a[j+1])
        {
            run_a->map[j] = '0';
            j++;
        }
        if (j == i)
        {
            run_a->map[i] = 'x';
            run_a->run_nb++;
        }
        else
        {
            run_a->map[i] = 's';
            run_a->map[j] = 'e';
            run_a->run_nb++;
        }
        i+=(j-i);
        i++;
    }
    return (free(array_a), SUCCESS);
}

void cdl_bottom_up_merge(t_circular_double_link_list * cdll_a, int * array_a, t_run * run_a, t_circular_double_link_list * cdll_b, int * array_b, t_run * run_b, t_i * i)
{
    size_t j;
    size_t k;
    size_t l;
    char direction;

    j = i->left;
    l = i->right;
    direction = 'r';
    if (run_a->run_nb <= run_b->run_nb)
    {
        direction = 'l';
        run_a->run_nb++;
        run_b->run_nb--;
    }
    else
    {
        run_a->run_nb--;
        run_b->run_nb++;
    }
    while (run_a->map[i->left] != 'e' && run_a->map[i->left] != 'x')
       i->left++; 
    while (run_b->map[i->right] != 'e' && run_b->map[i->right] != 'x')
       i->right++; 
    while (j <= i->left || l <= i->right)
    {
        if (j <= i->left && (l > i->right || array_a[j] > array_b[l]))
        {
            if (direction == 'l')
                r_rotate(cdll_a, 'a');
            else
            {
                r_rotate(cdll_a, 'a');
                push(cdll_b, cdll_a, 'b');
            }
            ++j;
        }
        else
        {
            if (direction == 'r')
                r_rotate(cdll_b, 'b');
            else
            {
                r_rotate(cdll_b, 'b');
                push(cdll_a, cdll_b, 'a');
            }
            ++l;
        }
    }
    i->left = j;
    i->right = l;
}
int cdl_bottom_up_merge_sort(t_circular_double_link_list * cdll_a, t_run * run_a, t_circular_double_link_list * cdll_b, t_run * run_b)
{
    int * array_a;
    int * array_b;
    t_i * i;

    do
    {
        array_a = cdl2array(cdll_a); 
        array_b = cdl2array(cdll_b); 
        set_run(cdll_a, run_a);
        set_run(cdll_b, run_b);
        if (!run_a->map ||!array_a || !run_b->map ||!array_b)
            return (free(array_a),free(array_b), free(run_a->map), free(run_b->map),ERROR);
        array_in_place_reverse(array_a, cdll_a->total); 
        array_in_place_reverse(array_b, cdll_b->total); 

        i->left = 0;
        i->right = 0;
        while (i->left < run_a->map_size && i->right < run_b->map_size)
        {
            cdl_bottom_up_merge(cdll_a, array_a, run_a, cdll_b, array_b, run_b, i);    
            print_cdl(cdll_a);
            print_map(run_a);
            print_cdl(cdll_b);
            print_map(run_b);

        }
        if (run_a->run_nb != 1 && run_b->run_nb != 1)
        {
            free(run_a->map);
            free(run_b->map);
            free(array_a);
            free(array_b);
        }
    }
    while (run_a->run_nb != 1 && run_b->run_nb != 1);

    return (free(array_a), free(array_b), SUCCESS);
}
