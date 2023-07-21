/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 19:24:09 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/21 13:25:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minirt.h>

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
	int	i;

	if (el)
	{
		if (el->cap)
		{
			i = 0;
			while (i < 2)
				free_scn_el(&el->cap[i++]);
			free(el->cap);
		}
		if (el->type != F_TYPE_UNDEF)
			free(el);
	}
}

void	clean_up(t_data *d)
{
	int			i;
	t_list		*next;

	while (d->all_scn_el)
	{
		next = d->all_scn_el->next;
		free_scn_el(d->all_scn_el->content);
		free(d->all_scn_el);
		d->all_scn_el = next;
	}
	i = 0;
	while (i < SCN_SIZE)
		free(d->scn_els[i++]);
}
