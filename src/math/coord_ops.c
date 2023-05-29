/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coord_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 10:49:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/29 12:49:17 by pmolnar       ########   odam.nl         */
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

t_coord3	*get_coord_diff(t_coord3 *p1, t_coord3 *p2)
{
	int			i;
	t_coord3	*diff;

	if (!p1 || !p2)
		return (NULL);
	diff = malloc(COORD_SIZE * sizeof(long double));
	i = 0;
	while (i < COORD_SIZE)
	{
		diff[i] = p2[i] - p1[i];
		i++;
	}
	return (diff);
}
