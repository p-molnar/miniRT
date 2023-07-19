/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:01:05 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/19 14:06:07 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <mrt_data_struct.h>
# include <mrt_macros.h>

//	parser
void		parse_input(t_data *scn, int argc, char *argv[]);
void		parse_elements(t_scn_el *el, char **input, unsigned int flags);
void		parse_type_identifier(t_scn_el *el, char *line);
void		add_cylinder_caps(t_scn_el *cylinder);

//	element parser
void		parse_coordinates(t_coord3 *coord, char *input);
void		parse_norm_vec(t_vec3 *vec, char *input);
void		parse_float(long double *f, char *input);
void		parse_range(long double *f, char *input, long double n_lower,
				long double n_upper);
void		parse_color(t_color *color, char *input, int n_lower, int n_upper);

//	free
void		free_arr(void **arr);
void		free_mx(t_mx *mx);
void		free_scn_el(t_scn_el *el);

//	helper
void		print_mx(t_mx *mx);
void		print_scene_el(t_scn_el *el);

//	parser utils
int			get_arr_size(char **arr);
int			open_file(char *file_name);
int			is_valid_number(char *c);

//	initialiser
void		init_scene(t_data *scn);
void		create_projection_plane(t_data *d);
void		set_up_scene(t_data *d);
void		populate_transformation_mx(t_scn_el *el);
t_ray		apply_transformations(t_ray ray, t_scn_el *obj_info);

//	error handling
int			error(t_err error);
void		warning(char *msg);

//	renderer
void		render_scene(t_data *d);
t_color		trace_ray(t_data *data, t_ray ray, const long double *range,
				int recursion_depth);

//	renderer/color
t_color		get_reflected_color(t_data *data, t_ray ray, t_ray sec_ray, int depth);
t_color		mix_colors(t_color local_color, t_color reflected_color,
				long double ref_factor);

//	lighting
long double	get_lighting_intensity(t_data *data, t_ray ray, t_ray reflection_ray, t_scn_el *obj);
long double	get_specular_lighting(t_ray ray, t_ray secondary_ray, t_vec3 obj_norm,
				long double intensity, long double spec);
t_closest	*cast_shadow(t_data *data, t_ray ray, long double *range);

//	util
// t_scn_el	**get_scn_els(t_list *list, int type);
t_scn_el	**get_scn_els(t_list *list, enum e_scn_el_type_flags type);
void		init_vec(t_vec3 **arr, int size);
t_vec3		get_reflection_ray(t_vec3 ray, t_vec3 norm);
t_coord3	get_incident_point(t_ray ray, t_closest *obj);
t_vec3		get_incident_point_norm(t_scn_el cam, t_coord3 inc_p, t_closest *obj);
void		set_up_camera_orientation(t_data *d);

//	math
t_vec3		create_vec(t_coord x, t_coord y, t_coord z);
long double	get_vec_len(t_vec3 vec);
t_vec3		get_normal_vec(t_vec3 vec);
void		normalize(t_vec3 *vec);

t_mx		get_inverse_mx(t_mx mx);
t_mx		multiply_mx(t_mx mx1, t_mx mx2);
t_mx		*get_scaling_mx(t_coord sx, t_coord sy, t_coord sz);
t_mx		get_translation_mx(t_coord tx, t_coord ty, t_coord tz);
t_mx		get_rotation_mx(t_mx axis, long double agl_r);
t_mx		coord_to_mx(t_coord3 coord, int r, int c, int val);
void		vec_to_mx(t_mx *mx, int r, int c, long double val);

int			is_in_range_f(long double n, long double n_lower,
				long double n_upper);
int			is_in_range_i(int n, int n_lower, int n_upper);
int			is_within_range_f(long double n, long double n_lower,
				long double n_upper);

long double	dot(t_vec3 vec_1, t_vec3 vec_2);
t_vec3		add(t_vec3 vec_1, t_vec3 vec_2);
t_vec3		scale(long double scaler, t_vec3 vec);
t_vec3		subtract(t_vec3 vec_1, t_vec3 vec_2);
t_vec3		cross(t_vec3 vec_1, t_vec3 vec_2);
t_coord3	offset(t_coord3 p, t_vec3 vec);

t_coord3	create_coord(long double x, long double y, long double z);
t_coord3	coord_subtract(t_coord3 c1, t_coord3 c2);
t_vec3		coord_to_vec(t_coord3 coord);
t_vec3		create_dir_vec(t_coord3 init_point, t_coord3 term_point);

long double	*quad_eq_solver(t_quad_param param, long double *discriminant);
long double	deg_to_rad(long double deg);
long double	rad_to_deg(long double rad);
long double	*get_euler_agls(t_mx *rot_mx);
long double	get_agl_between_d(t_vec3 vec_1, t_vec3 vec_2);
long double	get_agl_between(t_vec3 vec_1, t_vec3 vec_2);

//	color
t_color		get_rgba(int r, int g, int b, int a);
t_color		update_color_channel(t_color curr_color, t_color new_color,
				int channel);
t_color		get_color(t_color color, int channel);
t_color		get_r(int rgba);
t_color		get_g(int rgba);
t_color		get_b(int rgba);
t_color		get_a(int rgba);

//	render color
t_color	get_local_color(t_data *data, t_ray ray, t_ray reflection_ray, t_scn_el *closest_el);

// render util
void		draw_axes(t_data *data);
t_closest	*get_closest_el(t_scn_el **el, t_ray ray, const long double *range);
long double	*convert_to_viewport(int x, int y, long double *viewport,
				t_scn_el *cam);

//	elements
long double	get_sphere_intersections(t_ray ray, t_scn_el *obj);
long double	get_plane_intersection(t_ray ray, t_scn_el *obj);
long double	get_cylinder_intersection(t_ray ray, t_scn_el *obj, t_coord3 *inc_p);

#endif