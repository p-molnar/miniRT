/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 19:24:09 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/18 11:20:30 by pmolnar       ########   odam.nl         */
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

void	free_mx(t_mx *mx)
{
	if (mx)
	{
		free(mx->m);
		free(mx);
	}
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
		// if (el->translation)
		// 	free_mx(el->translation);
		// if (el->inv_translation)
		// 	free_mx(el->inv_translation);
		// if (el->rotation)
		// 	free_mx(el->rotation);
		// if (el->inv_rotation)
		// 	free_mx(el->inv_rotation);
		if (el->type != F_TYPE_UNDEF)
			free(el);
	}
}