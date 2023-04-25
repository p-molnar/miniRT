/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 13:09:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/25 09:43:58 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <libft.h>
#include <mrt_data_struct.h>

t_scn_el	**get_scn_els(t_list *list, t_el_type type)
{
	t_list		*tmp;
	t_scn_el	*curr_el;
	t_scn_el	**arr;
	int			i;

	i = 0;
	tmp = list;
	arr = NULL;
	while (tmp)
	{
		curr_el = tmp->content;
		if (curr_el->type == type)
		{
			arr = ft_realloc(arr, i * sizeof(t_scn_el *),
					(i + 2) * sizeof(t_scn_el *));
			arr[i] = curr_el;
			arr[i + 1] = NULL;
			i++;
		}
		tmp = tmp->next;
	}
	return (arr);
}
