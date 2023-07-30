/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:01:05 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/31 01:22:52 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <mrt_data_struct.h>
# include <mrt_macros.h>

//	parser
void		parse_input(t_data *scn, int argc, char *argv[]);
void		populate_data_fields(t_scn_el *el, char **input, unsigned int flags,
				t_line line_info);
void		parse_type_identifier(t_scn_el *el, char *line, t_line line_info);
void		add_cylinder_caps(t_scn_el *cylinder);

//	validator
void		validate_scn_el_setup(t_data *data);
void	validate_for_duplicate_el(enum e_scn_el_type_flags el_type,
								t_data *scn,
								t_line line_info);
void		validate_line_formatting(t_scn_el el, char **input,
				t_line line_info);

//	data_field_derivator
void		populate_derived_fields(t_scn_el *el);

//	element parser
void		parse_coordinates(t_coord3 *coord, char *input, t_line line_info);
void		parse_norm_vec(t_vec3 *vec, char *input, t_line line_info);
void		parse_float(long double *f, char *input, t_line line_info);
void		parse_range(long double *f, char *input, t_range range,
				t_line line_info);
void		parse_color(t_color *color, char *input, t_range range,
				t_line line_info);

//	free
void		free_arr(void **arr);
void		free_scn_el(t_scn_el *el);
void		clean_up(t_data *d);

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

//	renderer
void		render_scene(t_data *data, int width, int height);
t_color		trace_ray(t_data *data, t_ray ray, t_range range,
				int recursion_depth);

//	renderer/color
t_color		intensify_color(long double intensity, t_color color);
t_color		mix_colors(t_color c1, t_color c2);

//	lighting

long double	get_lighting_intensity(t_data *data, t_ray ray, t_hit_obj hit_obj);
long double	get_specular_intensity(t_ray *rays, long double intensity,
				long double spec);
t_hit_obj	is_element_in_way(t_data *data, t_ray ray, t_range range);

long double	yield_smallest_positive(long double *arr, int arr_size);
//	util
// t_scn_el	**get_scn_els(t_list *list, int type);
t_scn_el	**get_scn_els(t_list *list, enum e_scn_el_type_flags type);
void		set_up_scn_el_ptrs(t_data *d);
void		populate_window_properties(t_data *d);
void		get_incident_point(t_ray ray, t_hit_obj *obj);
void		get_surface_norm(t_scn_el cam, t_hit_obj *hit_obj);
void		set_up_ctw_mx(t_data *d);

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
t_vec3		vec_subtract(t_vec3 vec_1, t_vec3 vec_2);
t_vec3		cross(t_vec3 vec_1, t_vec3 vec_2);
t_coord3	offset(t_coord3 p, t_vec3 vec);

t_coord3	create_coord(long double x, long double y, long double z);
t_coord3	coord_subtract(t_coord3 c1, t_coord3 c2);
t_vec3		coord_to_vec(t_coord3 coord);
t_vec3		create_dir_vec(t_coord3 init_point, t_coord3 term_point);

long double	*quad_eq_solver(t_quad_param param, long double *discriminant);
long double	deg_to_rad(long double deg);
long double	get_agl_between(t_vec3 vec_1, t_vec3 vec_2);

//	color
uint32_t	update_color_channel(uint32_t curr_color, uint32_t new_val,
				int channel);
t_color		get_color(uint32_t color, int channel);

//	shader
t_color		get_local_color(t_data *data, t_ray ray, t_hit_obj hit_obj);
t_color		get_reflected_color(t_data *data, t_ray ray, t_hit_obj hit_obj,
				int refl_depth);

// render util
void		draw_axes(t_data *data);

//	elements
t_hit_obj	intersect(t_ray ray, t_scn_el **el, t_range range,
				enum e_isect mode);
long double	get_sphere_intersections(t_ray ray, t_scn_el *obj);
long double	get_plane_intersection(t_ray ray, t_scn_el *obj);
long double	get_cylinder_intersection(t_ray ray, t_scn_el *obj,
				t_coord3 *inc_p);

#endif