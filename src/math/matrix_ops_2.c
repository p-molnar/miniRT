/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 10:10:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/29 11:41:08 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

static void	populate_inv_mx_p2(long double *inv, long double *m)
{
	if (!inv || !m)
		return ;
	inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15]
		+ m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
	inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15]
		- m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
	inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15]
		+ m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
	inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14]
		- m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
	inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11]
		- m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
	inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11]
		+ m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
	inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11]
		- m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
	inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10]
		+ m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
	inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15]
		- m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
	inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14]
		+ m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
}

static void	populate_inv_mx_p1(long double *inv, long double *m)
{
	if (!inv || !m)
		return ;
	inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15]
		+ m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15]
		- m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15]
		+ m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
	inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14]
		- m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
	inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15]
		- m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15]
		+ m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
}

t_mx	*get_inverse_mx(t_mx *mx)
{
	int			i;
	long double	inv[16];
	long double	det;
	t_mx		*inv_mx;

	if (!mx)
		return (NULL);
	inv_mx = malloc(sizeof(t_mx));
	if (!inv_mx)
		return (NULL);
	inv_mx->c = mx->c;
	inv_mx->r = mx->r;
	inv_mx->m = malloc(4 * 4 * sizeof(long double));
	populate_inv_mx_p1(inv, mx->m);
	populate_inv_mx_p2(inv, mx->m);
	det = mx->m[0] * inv[0] + mx->m[1] * inv[4] + mx->m[2] * inv[8] + mx->m[3]
		* inv[12];
	if (det == 0)
		return (NULL);
	det = 1.0 / det;
	i = 0;
	while (i < 16)
	{
		inv_mx->m[i] = inv[i] * det;
		i++;
	}
	return (inv_mx);
}

t_mx	*expand_mx(t_mx *mx, int r, int c, long double val)
{
	t_mx	*exp_mx;
	int		row;
	int		col;
	int		v;

	if (!mx || (r <= mx->r && c <= mx->c))
		return (NULL);
	exp_mx = malloc(sizeof(t_mx));
	if (r > mx->r)
		exp_mx->r = r;
	else
		exp_mx->r = mx->r;
	if (c > mx->c)
		exp_mx->c = c;
	else
		exp_mx->c = mx->c;
	exp_mx->m = ft_calloc(exp_mx->r * exp_mx->c, sizeof(long double));
	row = 0;
	v = 0;
	while (row < exp_mx->r)
	{
		col = 0;
		while (col < exp_mx->c)
		{
			if (row < mx->r && col < mx->c)
				exp_mx->m[row * exp_mx->c + col] = mx->m[v++];
			else if (row == r - 1 && col == c - 1)
				exp_mx->m[row * exp_mx->c + col] = val;
			col++;
		}
		row++;
	}
	return (exp_mx);
}

t_mx	*coord_to_mx(t_coord3 *c)
{
	t_mx	*mx;

	if (!c)
		return (NULL);
	mx = malloc(sizeof(t_mx));
	mx->c = 3;
	mx->r = 1;
	mx->m = malloc(3 * sizeof(long double));
	if (!mx->m)
		return (NULL); // !free the whole thing!
	ft_memcpy(mx->m, c, 3 * sizeof(long double));
	return (mx);
}
