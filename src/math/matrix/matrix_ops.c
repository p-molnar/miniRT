/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:10:49 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/31 13:29:19 by pmolnar       ########   odam.nl         */
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

t_mx	*get_scaling_mx(t_coord3 sx, t_coord3 sy, t_coord3 sz)
{
	t_mx	*scale_mx;

	scale_mx = malloc(sizeof(t_mx));
	if (!scale_mx)
		return (NULL);
	scale_mx->r = 4;
	scale_mx->c = 4;
	scale_mx->m = ft_calloc(scale_mx->r * scale_mx->c, sizeof(long double));
	if (!scale_mx->m)
	{
		free(scale_mx);
		return (NULL);
	}
	scale_mx->m[0] = sx;
	scale_mx->m[5] = sy;
	scale_mx->m[10] = sz;
	scale_mx->m[15] = 1;
	return (scale_mx);
}

t_mx	*get_translation_mx(t_coord3 tx, t_coord3 ty, t_coord3 tz)
{
	t_mx	*trans_mx;

	trans_mx = malloc(sizeof(t_mx));
	if (!trans_mx)
		return (NULL);
	trans_mx->r = 4;
	trans_mx->c = 4;
	trans_mx->m = ft_calloc(trans_mx->r * trans_mx->c, sizeof(long double));
	if (!trans_mx->m)
	{
		free(trans_mx);
		return (NULL);
	}
	trans_mx->m[0] = 1;
	trans_mx->m[5] = 1;
	trans_mx->m[10] = 1;
	trans_mx->m[15] = 1;
	trans_mx->m[3] = tx;
	trans_mx->m[7] = ty;
	trans_mx->m[11] = tz;
	return (trans_mx);
}

t_mx	*get_rotation_mx2(long double a, long double b, long double g)
{
	t_mx				*rot_mx;
	long double			s[3];
	long double			c[3];

	s[0] = sin(a);
	s[1] = sin(b);
	s[2] = sin(g);
	c[0] = cos(a);
	c[1] = cos(b);
	c[2] = cos(g);

	rot_mx = malloc(sizeof(t_mx));
	if (!rot_mx)
		return (NULL);
	rot_mx->r = 4;
	rot_mx->c = 4;
	rot_mx->m = ft_calloc(rot_mx->r * rot_mx->c, sizeof(long double));
	if (!rot_mx->m)
	{
		free(rot_mx);
		return (NULL);
	}
	rot_mx->m[0] = c[1] * c[2];
	rot_mx->m[1] = s[0] * s[1] * c[2] - c[0] * s[2];
	rot_mx->m[2] = c[0] * s[1] * c[2] + s[0] * s[2];
	rot_mx->m[4] = c[1] * s[2];
	rot_mx->m[5] = s[0] * s[1] * s[2] - c[0] * c[2];
	rot_mx->m[6] = c[0] * s[1] * s[2] - s[0] * s[2];
	rot_mx->m[8] = -s[1];
	rot_mx->m[9] = s[0] * c[1];
	rot_mx->m[10] = c[0] * c[1];
	rot_mx->m[15] = 1;
	return (rot_mx);
}

t_mx	*get_rotation_mx(t_mx *axis, long double agl_r)
{
	t_mx				*rot_mx;
	const long double	agl_s = sin(agl_r);
	const long double	agl_c = cos(agl_r);

	rot_mx = malloc(sizeof(t_mx));
	if (!axis || !rot_mx)
		return (NULL);
	rot_mx->r = 4;
	rot_mx->c = 4;
	rot_mx->m = ft_calloc(rot_mx->r * rot_mx->c, sizeof(long double));
	if (!rot_mx->m)
	{
		free(rot_mx);
		return (NULL);
	}
	rot_mx->m[0] = agl_c + pow(axis->m[X], 2) * (1 - agl_c);
	rot_mx->m[1] = axis->m[X] * axis->m[Y] * (1 - agl_c) - axis->m[Z] * agl_s;
	rot_mx->m[2] = axis->m[X] * axis->m[Z] * (1 - agl_c) + axis->m[Y] * agl_s;
	rot_mx->m[4] = axis->m[Y] * axis->m[X] * (1 - agl_c) + axis->m[Z] * agl_s;
	rot_mx->m[5] = agl_c + pow(axis->m[Y], 2) * (1 - agl_c);
	rot_mx->m[6] = axis->m[Y] * axis->m[Z] * (1 - agl_c) - axis->m[X] * agl_s;
	rot_mx->m[8] = axis->m[Z] * axis->m[X] * (1 - agl_c) - axis->m[Y] * agl_s;
	rot_mx->m[9] = axis->m[Z] * axis->m[Y] * (1 - agl_c) + axis->m[X] * agl_s;
	rot_mx->m[10] = agl_c + pow(axis->m[Z], 2) * (1 - agl_c);
	rot_mx->m[15] = 1;
	return (rot_mx);
}
