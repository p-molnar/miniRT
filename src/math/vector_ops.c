/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:01:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/25 16:31:36 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>

#include <math.h>
#include <stdlib.h>

t_vec3	*create_vec(long double *init_point, long double *terminal_point)
{
	t_vec3				*vec;
	int					i;
	const long double	origin[3] = {0, 0, 0};

	if (!terminal_point)
		return (NULL);
	if (init_point == NULL)
		init_point = (long double *)origin;
	vec = malloc(sizeof(t_vec3));
	if (!vec)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		vec->dir[i] = terminal_point[i] - init_point[i];
		i++;
	}
	vec->len = get_vec_len(vec);
	return (vec);
}

long double	get_vec_len(t_vec3 *vec)
{
	long double	sum_of_sqrs;
	int			i;

	if (!vec)
		return (-1);
	sum_of_sqrs = 0;
	i = 0;
	while (i < COORD_SIZE)
	{
		sum_of_sqrs += pow(vec->dir[i], 2);
		i++;
	}
	return (sqrt(sum_of_sqrs));
}

t_vec3	*get_normal_vec(t_vec3 *vec)
{
	t_vec3	*normal;
	long double	len;
	int	i;

	if (!vec)
		return (NULL);
	len = get_vec_len(vec);
	normal = malloc(sizeof(t_vec3));
	if (!normal)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		if (len > 0)
			normal->dir[i] = vec->dir[i] / len;
		else
			normal->dir[i] = 0;	
		i++;
	}
	normal->len = 1;
	return (normal);
}
