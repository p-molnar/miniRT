/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/05 13:50:15 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>


t_color	trace_ray(t_data *data, t_ray *ray, const long double *range, int recursion_depth)
{
	t_closest			*closest_obj;
	t_color				color[2];
	long double			ref_factor;
	const long double	ref_range[RANGE_SIZE] = {EPS, INF};

	closest_obj = get_closest_el(data->scn_els[ALL_OBJS], ray, range);
	if (!closest_obj || !closest_obj->el)
		return (BACKGROUND_COLOR);
	// printf("original ray\n");
	// printf("origin: %Lf, %Lf, %Lf\n", ray->origin->x, ray->origin->y, ray->origin->z);
	// printf("dir: %Lf, %Lf, %Lf\n", ray->dir->dir.x, ray->dir->dir.y, ray->dir->dir.z);
	// printf("origin: %Lf, %Lf, %Lf\n", ray->origin->x, ray->origin->y, ray->origin->z);
	// printf("dir: %Lf, %Lf, %Lf\n", ray->dir->dir.x, ray->dir->dir.y, ray->dir->dir.z);
	data->p[INCIDENT] = get_incident_point(ray, closest_obj);
	// printf("inc_p: %Lf, %Lf, %Lf\n", data->p[INCIDENT]->x, data->p[INCIDENT]->y, data->p[INCIDENT]->z);
	data->v[NORM] = get_incident_point_norm(*data->scn_els[CAM], data->p[INCIDENT], closest_obj);
	// printf("norm: %Lf, %Lf, %Lf\n", data->v[NORM]->dir.x, data->v[NORM]->dir.y, data->v[NORM]->dir.z);
	// printf("- - - - - - - -\n");
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
			color = trace_ray(data, ray, range, 0);
			mlx_put_pixel(data->img, x, y, color);
			// free(ray.dir);
			x++;
		}
		y++;
	}
		draw_axes(data);
}
