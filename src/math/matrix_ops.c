/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:10:49 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/23 13:37:13 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_vec3	*translate(t_vec3 *vec, long double *translation_mx, int mx_dimension)
{
	// t_vec3		*vec;
	t_coord4	coord[COORD_SIZE + 1];
	t_coord3	new_coord[COORD_SIZE];
	long double	sum;
	int			i;
	int			j;
	(void)		mx_dimension;

	ft_memcpy(coord, vec->coord, COORD_SIZE * sizeof(long double));
	coord[3] = 1;
	sum = 0;
	i = 0;
	while(i < 3)
	{
		j = 0;
		while (j < 4)
		{
			sum += coord[i] * translation_mx[i + j];
			j++;
		}
		new_coord[i] = sum;
		sum = 0;
		i++;
	}
	return (create_vec(NULL, new_coord));
}

t_vec3	*vec_times_mx(t_vec3 *vec, long double *mx, int mx_dimension)
{
	long double new_coords[3];
	long double sum;
	int i;
	int j;

	sum = 0;
	i = 0;
	j = 0;
	while (i < mx_dimension)
	{
		sum += mx[i] * vec->coord[i % 3];
		if ((i + 1) % 3 == 0)
		{
			new_coords[j++] = sum;
			sum = 0;
		}
		i++;
	}
	return (create_vec(NULL, new_coords));
}