/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 11:13:10 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/03 16:19:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

t_color	trace_ray(t_data *data, long double *cam_coord,
		long double *pplane_coord)
{
	t_closest			*closest;
	t_color				color;
	const long double	range[RANGE_SIZE] = {1, INF};

	color = BACKGROUND_COLOR;
	data->vec[D] = create_vec(cam_coord, pplane_coord);
	closest = get_closest_el(data, cam_coord, data->vec[D], (long double *)range);
	if (closest->el != NULL)
	{
		data->vec[O] = create_vec(cam_coord, cam_coord);
		data->vec[Ds] = scale(closest->dist, data->vec[D]);
		data->vec[P] = add(data->vec[O], data->vec[Ds]);
		data->vec[N] = create_vec(closest->el->coord, data->vec[P]->coord);
		normalize_vec(data->vec[N]); // might not be needed
		color = compute_color(data, closest->el);
		// if (color != 255)
		// 	printf("color: %d\n", color);
	}
	free(closest);
	return (color);
}

void	render_img(t_data *data)
{
	int			canvas[2];
	int			screen[2];
	t_color		color;
	long double	*vp_coord;
	t_scn_el	**cam;

	cam = get_scn_els(data->scn_el, CAM);
	if (!cam)
		error(ft_strdup("No camera found"), EXIT, 1);
	canvas[X] = -CANVAS_W / 2;
	while (canvas[X] < CANVAS_W / 2)
	{
		canvas[Y] = CANVAS_H / 2;
		while (canvas[Y] > -CANVAS_H / 2)
		{
			screen[X] = canvas[X] + CANVAS_W / 2;
			screen[Y] = CANVAS_H / 2 - canvas[Y];
			init_vec(data->vec, PARAM_SIZE);
			vp_coord = convert_to_viewport(canvas[X], canvas[Y],
					data->viewport);
			color = trace_ray(data, cam[0]->coord, vp_coord);
			mlx_put_pixel(data->img, screen[X], screen[Y], color);
			free(vp_coord);
			free_vec(data->vec, PARAM_SIZE);
			canvas[Y]--;
		}
		canvas[X]++;
	}
	draw_axes(data);
	free(cam);
}
