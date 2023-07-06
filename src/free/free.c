/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/16 19:24:09 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/06 11:49:54 by pmolnar       ########   odam.nl         */
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

void	free_ray(t_ray *ray)
{
	if (ray)
	{
		if (ray->origin)
			free(ray->origin);
		if (ray->dir)
			free(ray->dir);
	}
	free(ray);
}

void	free_scn_el(t_scn_el *el)
{
	int	i;

	if (el)
	{
		if (el->n_vec)
			free(el->n_vec);
		if (el->cap)
		{
			i = 0;
			while (i < 2)
				free_scn_el(&el->cap[i++]);
		}
		if (el->translation)
			free(el->translation);
		if (el->inv_translation)
			free(el->inv_translation);
		if (el->rotation)
			free(el->rotation);
		if (el->inv_rotation)
			free(el->inv_rotation);
	}
}