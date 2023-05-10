/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 13:09:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/10 10:37:32 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <libft.h>
#include <mrt_data_struct.h>

void	init_vec(t_vec3 **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[i] = NULL;
		i++;
	}
}

t_scn_el	**get_scn_els(t_list *list, int type)
{
	t_list		*tmp;
	t_scn_el	*curr_el;
	t_scn_el	**arr;
	int			i;

	i = 0;
	tmp = list;
	arr = NULL;
	curr_el = NULL;
	while (tmp)
	{
		curr_el = tmp->content;
		if (curr_el && type & curr_el->type)
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
