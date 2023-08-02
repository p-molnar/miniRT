/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coord_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 10:49:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:37:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_coord3	create_coord(long double x, long double y, long double z)
{
	t_coord3	coord;

	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}

t_vec3	coord_to_vec(t_coord3 coord)
{
	t_vec3	vec;
	int		i;

	i = 0;
	while (i < COORD_SIZE)
	{
		vec.dir.coord[i] = coord.coord[i];
		i++;
	}
	vec.len = get_vec_len(vec);
	return (vec);
}

t_coord3	subtract_coord(t_coord3 c1, t_coord3 c2)
{
	t_coord3	diff;
	int			i;

	i = 0;
	while (i < COORD_SIZE)
	{
		diff.coord[i] = c1.coord[i] - c2.coord[i];
		i++;
	}
	return (diff);
}
