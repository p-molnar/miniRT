/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coord_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 10:49:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/08 10:52:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_coord3	*create_coord(long double x, long double y, long double z)
{
	t_coord3	*coord;

	coord = malloc(3 * sizeof(long double));
	if (!coord)
		return (NULL);
	coord[X] = x;
	coord[Y] = y;
	coord[Z] = z;
	return (coord);
}

t_vec3	*coord_to_vec(t_coord3 *coord)
{
	t_vec3	*vec;
	int		i;

	if (!coord)
		return (NULL);
	vec = malloc(sizeof(t_vec3));
	if (!vec)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		vec->dir[i] = coord[i];
		i++;
	}
	vec->len = get_vec_len(vec);
	return (vec);
}

t_coord3	*coord_subtract(t_coord3 *c1, t_coord3 *c2)
{
	int			i;
	t_coord3	*diff;

	if (!c1 || !c2)
		return (NULL);
	diff = malloc(COORD_SIZE * sizeof(long double));
	i = 0;
	while (i < COORD_SIZE)
	{
		diff[i] = c1[i] - c2[i];
		i++;
	}
	return (diff);
}
