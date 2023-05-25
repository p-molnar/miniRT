/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:10:49 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/24 23:11:17 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

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

t_mx	*multiply_mx(t_mx *mx1, t_mx *mx2)
{
	t_mx	*mx;
	int		mx_pos;
	int		i;
	int		j;

	if (!mx1 || !mx2 || (mx1->c != mx2->r))
		return (NULL);
	mx = ft_calloc(1, sizeof(t_mx));
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
	return (multiply_mx(mx, &scale_mx));
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
	return (multiply_mx(mx, &trans_mx));
}

t_mx	*rotate_mx(t_mx *mx, t_mx *axis, long double angle)
{
	t_mx		rotation_mx;
	long double	m[16];
	long double	angle_s;
	long double	angle_c;

	if (!mx || !axis)
		return (NULL);
	angle_s = sin(angle);
	angle_c = cos(angle);
	rotation_mx.r = 4;
	rotation_mx.c = 4;
	rotation_mx.m = m;
	ft_memset(m, 0, 16 * sizeof(long double));
	m[0] = angle_c + pow(axis->m[0], 2) * (1 - angle_c);
	m[1] = axis->m[0] * axis->m[1] * (1 - angle_c) - axis->m[2] * angle_s;
	m[2] = axis->m[0] * axis->m[2] * (1 - angle_c) + axis->m[1] * angle_s;
	m[4] = axis->m[1] * axis->m[0] * (1 - angle_c) + axis->m[2] * angle_s;
	m[5] = angle_c + pow(axis->m[1], 2) * (1 - angle_c);
	m[6] = axis->m[1] * axis->m[2] * (1 - angle_c) - axis->m[0] * angle_s;
	m[8] = axis->m[2] * axis->m[0] * (1 - angle_c) - axis->m[1] * angle_s;
	m[9] = axis->m[2] * axis->m[1] * (1 - angle_c) + axis->m[0] * angle_s;
	m[10] = angle_c + pow(axis->m[2], 2) * (1 - angle_c);
	m[15] = 1;
	return (multiply_mx(mx, &rotation_mx));
}
