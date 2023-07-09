/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:01:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/08 15:16:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <minirt.h>

t_vec3	*create_vec(t_coord x, t_coord y, t_coord z)
{
	t_vec3	*vec;

	vec = malloc(sizeof(t_vec3));
	if (!vec)
		return (NULL);
	vec->dir.x = x;
	vec->dir.y = y;
	vec->dir.z = z;
	vec->len = get_vec_len(vec);
	return (vec);
}

t_vec3	*create_dir_vec(t_coord3 init_point, t_coord3 term_point)
{
	t_vec3		*dir;
	t_coord3	*coord_diff;

	coord_diff = coord_subtract(term_point, init_point);
	dir = coord_to_vec(*coord_diff);
	free(coord_diff);
	return (dir);
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
		sum_of_sqrs += pow(vec->dir.coord[i], 2);
		i++;
	}
	return (sqrt(sum_of_sqrs));
}

void	normalize(t_vec3 *vec)
{
	int	i;

	if (!vec)
		return ;
	i = 0;
	while (i < COORD_SIZE)
	{
		if (vec->len > 0)
			vec->dir.coord[i] = vec->dir.coord[i] / vec->len;
		else
			vec->dir.coord[i] = 0;
		i++;
	}
	vec->len = 1;
}

t_vec3	*get_normal_vec(t_vec3 *vec)
{
	t_vec3	*new_vec;

	new_vec = malloc(sizeof(t_vec3));
	if (!new_vec)
		return (NULL);
	ft_memcpy(new_vec, vec, sizeof(t_vec3));
	normalize(new_vec);
	return (new_vec);
}
