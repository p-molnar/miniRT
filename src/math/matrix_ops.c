/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:10:49 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/24 16:53:26 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3	*vec_times_mx(t_vec3 *vec, long double *mx, int mx_dimension)
{
	long double	new_coords[3];
	long double	sum;
	int			i;
	int			j;

	sum = 0;
	i = 0;
	j = 0;
	while (i < mx_dimension)
	{
		sum += mx[i] * vec->dir[i % 3];
		if ((i + 1) % 3 == 0)
		{
			new_coords[j++] = sum;
			sum = 0;
		}
		i++;
	}
	return (create_vec(NULL, new_coords));
}

static long double	calc_dot(int row, int col, t_mx *mx1, t_mx *mx2)
{
	long double	dot;
	int			i;

	dot = 0;
	i = 0;
	while (i < mx1->c)
	{
		dot += mx1->m[row * mx1->r + i] * mx2->m[col + i * mx2->c];
		i++;
	}
	return (dot);
}

t_mx	*mx_times_mx(t_mx *mx1, t_mx *mx2)
{
	t_mx	*mx;
	int		mx_pos;
	int		i;
	int		j;

	if (!mx1 || !mx2 || (mx1->c != mx2->r))
		return (NULL);
	mx = ft_calloc(1, sizeof(mx));
	if (!mx)
		return (mx);
	mx->r = mx1->r;
	mx->c = mx2->c;
	mx->m = malloc(mx->r * mx->c * sizeof(long double));
	mx_pos = 0;
	i = 0;
	while (i < mx1->r)
	{
		j = 0;
		while (j < mx2->c)
		{
			mx->m[mx_pos++] = calc_dot(i, j, mx1, mx2);
			j++;
		}
		i++;
	}
	return (mx);
}

t_mx	*scale_mx(t_mx *mx, t_coord3 sx, t_coord3 sy, t_coord3 sz)
{
	t_mx		scale_mx;
	long double	m[16];

	scale_mx.r = 4;
	scale_mx.c = 4;
	scale_mx.m = m;
	ft_memset(m, 0, 16 * sizeof(long double));
	m[0] = sx;
	m[5] = sy;
	m[10] = sz;
	m[15] = 1;
	return (mx_times_mx(mx, &scale_mx));
}

t_mx	*translate_mx(t_mx *mx, t_coord3 tx, t_coord3 ty, t_coord3 tz)
{
	t_mx		trans_mx;
	long double	m[16];

	trans_mx.r = 4;
	trans_mx.c = 4;
	trans_mx.m = m;
	ft_memset(m, 0, 16 * sizeof(long double));
	m[0] = 1;
	m[5] = 1;
	m[10] = 1;
	m[15] = 1;
	m[3] = tx;
	m[6] = ty;
	m[9] = tz;
	return (mx_times_mx(mx, &trans_mx));
}

t_mx	*rotate_mx(t_mx *mx, long double rotation)
{
	t_mx		rotation_mx;
	long double	m[16];

	rotation_mx.r = 4;
	rotation_mx.c = 4;
	rotation_mx.m = m;
	ft_memset(m, 0, 16 * sizeof(long double));
	m[0] = 1;
	m[15] = 1;
	m[5] = cos(rotation);
	m[6] = -1 * sin(rotation);
	m[10] = sin(rotation);
	m[11] = cos(rotation);
	return (mx_times_mx(mx, &rotation_mx));
}

t_mx3	*create_rotation_mx3(long double theta, t_vec3 *axis)
{
	long double	sin_t;
	long double	cos_t;
	t_coord3	*u;
	t_mx3		*mx;

	sin_t = sin(deg_to_rad(theta));
	cos_t = cos(deg_to_rad(theta));
	u = axis->n_dir;
	mx = malloc(9 * sizeof(long double));
	mx[0] = cos_t + pow(u[0], 2) * (1 - cos_t);
	mx[1] = u[0] * u[1] * (1 - cos_t) - u[2] * sin_t;
	mx[2] = u[0] * u[2] * (1 - cos_t) + u[1] * sin_t;
	mx[3] = u[1] * u[0] * (1 - cos_t) + u[2] * sin_t;
	mx[4] = cos_t + pow(u[1], 2) * (1 - cos_t);
	mx[5] = u[1] * u[2] * (1 - cos_t) - u[0] * sin_t;
	mx[6] = u[2] * u[0] * (1 - cos_t) - u[1] * sin_t;
	mx[7] = u[2] * u[1] * (1 - cos_t) + u[0] * sin_t;
	mx[8] = cos_t + pow(u[2], 2) * (1 - cos_t);
	return (mx);
}
