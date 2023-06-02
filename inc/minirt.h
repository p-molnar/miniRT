/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:01:05 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/02 11:11:45 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <mrt_data_struct.h>
# include <mrt_macros.h>

//	parser
void		parse_scene(t_data *scn, int argc, char *argv[]);
void		parse_elements(t_scn_el *el, char **input, unsigned int flags);
void		parse_type_identifier(t_scn_el *el, char *line);

//	element parser
void		parse_coordinates(long double *coord, char *input);
void		parse_norm_vec(t_vec3 **vec, char *input);
void		parse_float(long double *f, char *input);
void		parse_range(long double *f, char *input, long double n_lower,
				long double n_upper);
void		parse_color(t_color *color, char *input, int n_lower, int n_upper);

//	free
void		free_arr(void **arr);

//	parser utils
int			get_arr_size(char **arr);
int			open_file(char *file_name);
int			is_valid_number(char *c);

//	initialiser
void		init_scene(t_data *scn);
void		create_projection_plane(t_data *d);
void		set_up_vars(t_data *d);

//	error handling
int			error(char *msg, int exit_method, int exit_code);
void		warning(char *msg);

//	renderer
void		render_img(t_data *d);
t_color		trace_ray(t_data *data, long double *start_coord, t_vec3 *dir,
				const long double *range, int recursion_depth);

//	renderer/color
t_color		get_reflected_color(t_data *data, t_vec3 *dir,
				const long double *range, int depth);
t_color		mix_colors(t_color local_color, t_color reflected_color,
				long double ref_factor);

//	lighting
long double	get_lighting_intensity(t_data *data, t_coord3 *inc_p,
				t_scn_el *obj);
long double	get_diffuse_lighting(t_data *data, t_scn_el *light);
long double	get_specular_lighting(t_vec3 *dir, t_vec3 *light, t_vec3 *obj_norm,
				long double intensity, long double spec);
t_closest	*cast_shadow(t_data *data, t_coord3 *inc_p, t_vec3 *dir,
				long double *range);

//	util
t_scn_el	**get_scn_els(t_list *list, int type);
void		init_vec(t_vec3 **arr, int size);
void		free_vec(t_vec3 **arr, int size);
t_vec3		*get_ray_reflection(t_vec3 *ray, t_vec3 *norm);
t_coord3	*get_incident_point(t_coord3 *origin, t_vec3 *dir, t_closest *obj);

//	math
t_vec3		*create_vec(long double *init_point, long double *terminal_point);
long double	get_vec_len(t_vec3 *vec);
t_vec3		*get_normal_vec(t_vec3 *vec);

t_mx		*get_inverse_mx(t_mx *mx);
t_mx		*multiply_mx(t_mx *mx1, t_mx *mx2);
t_mx		*get_scaling_mx(t_coord3 sx, t_coord3 sy, t_coord3 sz);
t_mx		*get_translation_mx(t_coord3 tx, t_coord3 ty, t_coord3 tz);
t_mx		*get_rotation_mx(t_mx *axis, long double rot_angle);
t_mx		*get_rotation_mx2(long double a, long double b, long double g);
t_mx		*coord_to_mx(t_coord3 *coord, int r, int c);
t_mx		*expand_mx(t_mx *mx, int r, int c, long double val);

//	transformation
t_coord3	*get_SiRiTi(t_coord3 *c, t_coord3 *obj_coord);
t_coord3	*get_TRS(t_coord3 *c, t_coord3 *obj_coord);
t_coord3	*get_RSi(t_coord3 *c, t_coord3 *obj_coord);
t_coord3	*get_Siri(t_coord3 *c, t_coord3 *obj_coord);

int			is_in_range_f(long double n, long double n_lower,
				long double n_upper);
int			is_in_range_i(int n, int n_lower, int n_upper);
int			is_within_range_f(long double n, long double n_lower,
				long double n_upper);

long double	dot(t_vec3 *vec_1, t_vec3 *vec_2);
t_vec3		*add(t_vec3 *vec_1, t_vec3 *vec_2);
t_vec3		*scale(long double scaler, t_vec3 *vec);
t_vec3		*subtract(t_vec3 *vec_1, t_vec3 *vec_2);
t_vec3		*vec_times_mx(t_vec3 *vec, long double *mx, int mx_dimension);
t_vec3		*cross(t_vec3 *vec_1, t_vec3 *vec_2);
t_coord3	*offset(t_coord3 *p, t_vec3 *vec);

t_coord3	*create_coord(long double x, long double y, long double z);
t_coord3	*get_coord_diff(t_coord3 *p1, t_coord3 *p2);

long double	*quad_eq_solver(long double a,
							long double b,
							long double c,
							long double *disc);
long double	deg_to_rad(long double deg);
long double	rad_to_deg(long double rad);
long double	*get_euler_agls(t_mx *rot_mx);
long double	get_agl_between_d(t_vec3 *vec_1, t_vec3 *vec_2);
long double	get_agl_between_r(t_vec3 *vec_1, t_vec3 *vec_2);


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
t_color		get_incident_point_color(t_data *data, t_coord3 *inc_p,
				t_scn_el *closest_el);

// render util
void		draw_axes(t_data *data);
t_closest	*get_closest_el(t_scn_el **el, t_coord3 *origin, t_vec3 *dir,
				const long double *range);
long double	*convert_to_viewport(int x, int y, long double *viewport,
				t_scn_el *cam);

//	elements
long double	get_sphere_intersections(long double *origin, t_vec3 *dir,
				t_scn_el *obj);
long double	get_plane_intersection(t_coord3 *origin, t_vec3 *dir,
				t_scn_el *obj);
long double	get_cylinder_intersection(t_coord3 *origin, t_vec3 *dir,
				t_scn_el *obj);

#endif