/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:59:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/12 21:30:29 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	populate_cylinder_properties(t_scn_el *cap, t_scn_el *cy, char cap_type)
{
	int			is_btm;
	t_coord3	*norm;
	t_coord		std_pos[3] = {0, 0, 0};

	is_btm = cap_type == 'B';
	cap->type = F_CYLINDER_CAP;
	cap->color = cy->color;
	cap->reflection = cy->reflection;
	cap->specular = cy->specular;
	cap->pos.x = 0;
	cap->pos.y = 0;
	if (is_btm)
	{
		cap->pos.z = std_pos[Z] - (cy->height / 2);
		norm = create_coord(cap->pos.x, cap->pos.y, cap->pos.z - 1);
	}
	else
	{
		cap->pos.z = std_pos[Z] + (cy->height / 2);
		norm = create_coord(cap->pos.x, cap->pos.y, cap->pos.z + 1);
	}
	cap->n_vec = create_dir_vec(cap->pos, *norm);
}

void	add_cylinder_caps(t_scn_el *cylinder)
{
	t_scn_el	*caps;

	caps = ft_calloc(2, sizeof(t_scn_el));
	populate_cylinder_properties(&caps[0], cylinder, 'B');
	populate_cylinder_properties(&caps[1], cylinder, 'T');
	cylinder->cap = caps;
}

long double	yield_smallest_positive(long double *arr)
{
	int	i;
	long double	smallest;

	smallest = (unsigned int) -1;
	i = 0;	
	while (i < 4)
	{
		if (arr[i] > 0 && arr[i] < smallest)
			smallest = arr[i];
		i++;
	}
	if (smallest == (unsigned int) -1)
		smallest = -1;
	return (smallest);
}

long double	get_cylinder_intersection(t_ray *ray, t_scn_el *obj)
{
	t_quad_param param;
	long double *t;
	long double	z[2];
	long double	intersect[4] = {-1, -1, -1, -1};
	long double	r;

	param.a = pow(ray->dir->dir.x, 2) + pow(ray->dir->dir.y, 2);
	param.b = 2 * (ray->origin->x * ray->dir->dir.x + ray->origin->y * ray->dir->dir.y);
	param.c = pow(ray->origin->x, 2) + pow(ray->origin->y, 2) - 1;
	t = quad_eq_solver(param, NULL);
	if (t != NULL)
	{
		intersect[0] = t[0];
		intersect[1] = t[1];
		printf("i[0] = %Lf, i[1] = %Lf\n", intersect[0], intersect[1]);
		z[0] = ray->origin->z + t[0] * ray->dir->dir.z;
		z[1] = ray->origin->z + t[1] * ray->dir->dir.z;
		if (!(z[0] > obj->cap[0].pos.z && z[0] < obj->cap[1].pos.z))
			intersect[0] = -1;
		if (!(z[1] > obj->cap[0].pos.z && z[1] < obj->cap[1].pos.z))
			intersect[1] = -1;
		free(t);
		printf("Z[0] = %Lf, Z[1] = %Lf\n", z[0], z[1]);
		if ((z[0] < obj->cap[0].pos.z && z[1] > obj->cap[0].pos.z) ||
			(z[0] > obj->cap[0].pos.z && z[1] < obj->cap[0].pos.z))
		{
			intersect[2] = (obj->cap[0].pos.z - ray->origin->z) / ray->dir->dir.z;
			printf("bottom cap\n");
			printf("intersect1: %Lf\n", intersect[2]);
		}
		if ((z[0] < obj->cap[1].pos.z && z[1] > obj->cap[1].pos.z) ||
			(z[0] > obj->cap[1].pos.z && z[1] < obj->cap[1].pos.z))
		{
			intersect[3] = (obj->cap[1].pos.z - ray->origin->z) / ray->dir->dir.z;
			printf("top cap\n");
			printf("intersect2: %Lf\n", intersect[3]);
		}
		r = yield_smallest_positive(intersect);
	}
	else
		r = -1;

	if (r != -1)
		printf("r: %Lf\n", r);
	return (r);
	// intersect[2] = get_plane_intersection(ray, &obj->cap[0]);
	// long double x = ray->origin->x + intersect[2] * ray->dir->dir.x;
	// long double y = ray->origin->y + intersect[2] * ray->dir->dir.y;
	// if (pow(x, 2) + pow(y, 2) > pow(obj->diameter / 2.0, 2))
	// 	intersect[2] = -1;
	// intersect[3] = get_plane_intersection(ray, &obj->cap[1]);
	// x = ray->origin->x + intersect[3] * ray->dir->dir.x;
	// y = ray->origin->y + intersect[3] * ray->dir->dir.y;
	// if (pow(x, 2) + pow(y, 2) > pow(obj->diameter / 2.0, 2))
	// 	intersect[3] = -1;
	// r = yield_smallest_positive(intersect);
	// // printf("1: %Lf, 2: %Lf, 3: %Lf, 4: %Lf\n", intersect[0], intersect[1], intersect[2], intersect[3]);
	// // printf("r: %Lf\n", r);
	// return (r);
}
