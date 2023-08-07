/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 13:09:33 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/07 10:44:43 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <libft.h>
#include <mrt_data_struct.h>
#include <mrt_error.h>

t_scn_el	**get_scn_els(t_list *list, enum e_scn_el_type_flags lookup_type)
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
		if (curr_el && curr_el->type & lookup_type)
		{
			arr = ft_realloc(arr, i * sizeof(t_scn_el *),
					(i + 2) * sizeof(t_scn_el *));
			if (arr == NULL)
				error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
			arr[i] = curr_el;
			arr[i + 1] = NULL;
			i++;
		}
		tmp = tmp->next;
	}
	return (arr);
}
