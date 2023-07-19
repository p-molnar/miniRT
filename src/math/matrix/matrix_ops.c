/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:10:49 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/18 12:44:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

static long double	calc_dot(int row, int col, t_mx mx1, t_mx mx2)
{
	long double	dot;
	int			i;

	dot = 0;
	i = 0;
	while (i < mx1.c)
	{
		dot += mx1.m[row * mx1.r + i] * mx2.m[col + i * mx2.c];
		i++;
	}
	return (dot);
}

t_mx	multiply_mx(t_mx mx1, t_mx mx2)
{
	t_mx	mx;
	int		mx_pos;
	int		i;
	int		j;

	mx.r = mx1.r;
	mx.c = mx2.c;
	mx_pos = 0;
	i = 0;
	while (i < mx1.r)
	{
		j = 0;
		while (j < mx2.c)
		{
			mx.m[mx_pos++] = calc_dot(i, j, mx1, mx2);
			j++;
		}
		i++;
	}
	return (mx);
}

t_mx	get_translation_mx(t_coord tx, t_coord ty, t_coord tz)
{
	t_mx	trans_mx;

	trans_mx.r = 4;
	trans_mx.c = 4;
	ft_bzero(&trans_mx.m, 16);
	trans_mx.m[0] = 1;
	trans_mx.m[5] = 1;
	trans_mx.m[10] = 1;
	trans_mx.m[15] = 1;
	trans_mx.m[3] = tx;
	trans_mx.m[7] = ty;
	trans_mx.m[11] = tz;
	return (trans_mx);
}

t_mx	get_rotation_mx(t_mx axis, long double agl_r)
{
	t_mx				rot_mx;
	const long double	agl_s = sin(agl_r);
	const long double	agl_c = cos(agl_r);

	rot_mx.r = 4;
	rot_mx.c = 4;
	ft_bzero(&rot_mx.m, 16 * sizeof(long double));
	rot_mx.m[0] = agl_c + pow(axis.m[X], 2) * (1 - agl_c);
	rot_mx.m[1] = axis.m[X] * axis.m[Y] * (1 - agl_c) - axis.m[Z] * agl_s;
	rot_mx.m[2] = axis.m[X] * axis.m[Z] * (1 - agl_c) + axis.m[Y] * agl_s;
	rot_mx.m[4] = axis.m[Y] * axis.m[X] * (1 - agl_c) + axis.m[Z] * agl_s;
	rot_mx.m[5] = agl_c + pow(axis.m[Y], 2) * (1 - agl_c);
	rot_mx.m[6] = axis.m[Y] * axis.m[Z] * (1 - agl_c) - axis.m[X] * agl_s;
	rot_mx.m[8] = axis.m[Z] * axis.m[X] * (1 - agl_c) - axis.m[Y] * agl_s;
	rot_mx.m[9] = axis.m[Z] * axis.m[Y] * (1 - agl_c) + axis.m[X] * agl_s;
	rot_mx.m[10] = agl_c + pow(axis.m[Z], 2) * (1 - agl_c);
	rot_mx.m[15] = 1;
	return (rot_mx);
}
