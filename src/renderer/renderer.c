/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/06 15:23:36y pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3	*get_incident_point_norm(t_coord3 *inc_p, t_closest *obj)
{
	t_vec3	*obj_norm;

	obj_norm = NULL;
	if (obj->el->type == F_CYLINDER)
	{
		if ((inc_p[Z] > obj->el->cap[0].pos[Z] && inc_p[Z] < obj->el->cap[1].pos[Z]))
		{
			t_coord3 *cy_inc_p_depth = create_coord(0, 0, inc_p[Z]);
			obj_norm = create_dir_vec(cy_inc_p_depth, inc_p);
		}
		else
		{
			if (inc_p[Z] <= obj->el->cap[0].pos[Z])
				obj_norm = coord_to_vec(obj->el->cap[0].n_vec->dir);
			else
				obj_norm = coord_to_vec(obj->el->cap[1].n_vec->dir);
		}
	}
	else if (obj->el->type == F_SPHERE)
		obj_norm = create_dir_vec(obj->el->pos, inc_p);
	else if (obj->el->type == F_PLANE)
	{	
		obj_norm = coord_to_vec(obj->el->n_vec->dir);
	}
	normalize(obj_norm);
	return (obj_norm); 
}

t_color	trace_ray(t_data *data, long double *origin, t_vec3 *dir,
		const long double *range, int recursion_depth)
{
	t_closest			*closest_obj;
	t_scn_el			**el_arr;
	t_color				color[2];
	long double			ref_factor;
	const long double	ref_range[RANGE_SIZE] = {EPS, INF};

	el_arr = get_scn_els(data->all_scn_el, G_OBJS);
	closest_obj = get_closest_el(el_arr, origin, dir, range);
	if (!closest_obj || !closest_obj->el)
		return (BACKGROUND_COLOR);
	data->p[INCIDENT] = get_incident_point(origin, dir, closest_obj);
	data->v[NORM] = get_incident_point_norm(data->p[INCIDENT], closest_obj);
	color[0] = get_incident_point_color(data, data->p[INCIDENT], closest_obj->el);
	ref_factor = closest_obj->el->reflection;
	free(closest_obj);
	if (recursion_depth <= 0 || ref_factor <= 0)
		return (color[0]);
	color[1] = get_reflected_color(data, dir, ref_range, recursion_depth);
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
	t_mx *origin = coord_to_mx(create_coord(0, 0, 0), 3, 1);
	origin = expand_mx(origin, 4, 1, 1);
	printf("origin mx: \n");
	print_mx(origin);
	origin = multiply_mx(data->ctw_mx, origin);
	printf("multiplied mx: \n");
	print_mx(origin);
	ray->origin = create_coord(origin->m[X], origin->m[Y], origin->m[Z]);
	double fov_scale = tan(deg_to_rad((*data->scn_el[CAM])->fov / 2));
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
			// printf("origin: %Lf, %Lf, %Lf\n", ray->origin[0], ray->origin[1], ray->origin[2]);
			// printf("%LF, %Lf, %Lf\n", ray->dir->dir[0], ray->dir->dir[1], ray->dir->dir[2]);
			normalize(ray->dir);
			// printf("normalised: %LF, %Lf, %Lf\n", ray->dir->dir[0], ray->dir->dir[1], ray->dir->dir[2]);
			color = trace_ray(data, ray->origin, ray->dir, range, 0);
			mlx_put_pixel(data->img, x, y, color);
			// free(ray.dir);
			x++;
		}
		y++;
	}
		// draw_axes(data);
}
