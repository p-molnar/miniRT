/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/12 22:48:50 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3	*get_incident_point_norm(t_scn_el *cam, t_coord3 *inc_p, t_closest *obj)
{
	t_vec3	*obj_norm;

	obj_norm = NULL;
	printf("inc_p: %.20Lf, %.20Lf, %.20f\n", inc_p->x, inc_p->y, (float) inc_p->z);
	printf("cap0z: %.20Lf\n", obj->el->cap[0].pos.z);
	printf("cap1z: %.20Lf\n", obj->el->cap[1].pos.z);
	if (obj->el->type == F_CYLINDER)
	{
		if (((float) inc_p->z > obj->el->cap[0].pos.z && (float) inc_p->z < obj->el->cap[1].pos.z))
		{
			printf("cy body\n");
			t_coord3 *cy_inc_p_depth = create_coord(0, 0, inc_p->z);
			obj_norm = create_dir_vec(*cy_inc_p_depth, *inc_p);
		}
		else
		{
			printf("cy cap\n");
			if (cam->pos.z <= inc_p->z)
				obj_norm = create_vec(0, 0, -1);
			else
				obj_norm = create_vec(0, 0, 1);

			// if (inc_p->z <= obj->el->cap[0].pos.z)
			// 	obj_norm = coord_to_vec(obj->el->cap[0].n_vec->dir);
			// else
			// 	obj_norm = coord_to_vec(obj->el->cap[1].n_vec->dir);
		}
	}
	else if (obj->el->type == F_SPHERE)
		obj_norm = create_dir_vec(obj->el->pos, *inc_p);
	else if (obj->el->type == F_PLANE)
	{	
		obj_norm = coord_to_vec(obj->el->n_vec->dir);
	}
	normalize(obj_norm);
	printf("norm: %Lf, %Lf, %Lf\n", obj_norm->dir.x, obj_norm->dir.y, obj_norm->dir.z);
	return (obj_norm); 
}

t_color	trace_ray(t_data *data, t_ray *ray, const long double *range, int recursion_depth)
{
	t_closest			*closest_obj;
	t_color				color[2];
	long double			ref_factor;
	const long double	ref_range[RANGE_SIZE] = {EPS, INF};

	closest_obj = get_closest_el(data->scn_els[ALL_OBJS], ray, range);
	// printf("closest_obj: %p\n", closest_obj->el);
	if (!closest_obj || !closest_obj->el)
		return (BACKGROUND_COLOR);
	data->p[INCIDENT] = get_incident_point(ray, closest_obj);
	data->v[NORM] = get_incident_point_norm(*data->scn_els[CAM], data->p[INCIDENT], closest_obj);
	color[0] = get_incident_point_color(data, ray, data->p[INCIDENT], closest_obj->el);
	ref_factor = closest_obj->el->reflection;
	free(closest_obj);
	if (recursion_depth <= 0 || ref_factor <= 0)
		return (color[0]);
	color[1] = get_reflected_color(data, ray, ref_range, recursion_depth);
	return (mix_colors(color[0], color[1], ref_factor));
}

void	render_scene(t_data *data)
{
	int	y;
	int	x;
	long double	pixel_x;
	long double	pixel_y;
	double		aspect_ratio;
	const long double	range[RANGE_SIZE] = {1, INF};
	t_color	color;

	color = 0;
	aspect_ratio = CANVAS_W / CANVAS_H; 
	y = 0;
	t_ray *ray = malloc(sizeof(t_ray));
	ray->origin = &data->scn_els[CAM][0]->pos;
	double fov_scale = tan(deg_to_rad((*data->scn_els[CAM])->fov / 2));
	while (y < CANVAS_H)
	{
		x = 0;
		while (x < CANVAS_W)
		{
		    pixel_x = (2 * ((x + 0.5) / CANVAS_W) - 1) * fov_scale * aspect_ratio;
      		pixel_y = (1 - 2 * (y + 0.5) / CANVAS_H) * fov_scale;
			
			t_mx *dir_mx = coord_to_mx(create_coord(pixel_x, pixel_y, 1), 3, 1);
			dir_mx = expand_mx(dir_mx, 4, 1, 0);
			// printf("dir mx: \n");
			// print_mx(dir_mx);
			dir_mx = multiply_mx(data->ctw_mx, dir_mx);
			// printf("multiplied mx: \n");
			// print_mx(dir_mx);
			ray->dir = create_vec(dir_mx->m[X], dir_mx->m[Y], dir_mx->m[Z]);
			// printf("origin: %Lf, %Lf, %Lf\n", ray->origin->x, ray->origin->y, ray->origin->z);
			// printf("%LF, %Lf, %Lf\n", ray->dir->dir.x, ray->dir->dir.y, ray->dir->dir.z);
			normalize(ray->dir);
			// printf("normalized: %LF, %Lf, %Lf\n", ray->dir->dir.x, ray->dir->dir.y, ray->dir->dir.z);
			color = trace_ray(data, ray, range, 2);
			mlx_put_pixel(data->img, x, y, color);
			// free(ray.dir);
			x++;
		}
		y++;
	}
		draw_axes(data);
}
