/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 19:24:09 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/07 11:08:22 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minirt.h>
#include <stdio.h>

void	free_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
}

void	free_scn_el(t_scn_el *el)
{
	if (el)
	{
		if (el->cap)
			free(el->cap);
		free(el);
	}
}

void	clean_up(t_data *d)
{
	int			i;
	t_list		*next;

	while (d->scn_el_list)
	{
		next = d->scn_el_list->next;
		free_scn_el(d->scn_el_list->content);
		free(d->scn_el_list);
		d->scn_el_list = next;
	}
	i = 0;
	while (i < SCN_SIZE)
	{
		if (d->scn_el[i])
			free(d->scn_el[i]);
		i++;
	}
}
