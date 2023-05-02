/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:01:05 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/02 10:42:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mrt_data_struct.h>

//	parser
void		parse_scene(t_data *scn, int argc, char *argv[]);
void		parse_elements(t_scn_el *el, char **input, unsigned int flags);
void		parse_type_identifier(t_scn_el *el, char *line);

//	element parser
void		parse_coordinates(long double *coord, char *input);
void		parse_norm_vec(long double *coord, char *input);
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

//	error handling
int			error(char *msg, int exit_method, int exit_code);
void		warning(char *msg);

//	renderer
void		render_img(t_data *d);
// int			get_computed_color(t_data *data, t_scn_el *closest_el);
int			get_computed_color(t_data *data, t_color color);

//	lighting
long double	compute_lighting_intensity(t_data *data);

//	util
t_scn_el	**get_scn_els(t_list *list, int type);
void		init_vec(t_vec **arr, int size);
void		free_vec(t_vec **arr, int size);

//	math
t_vec		*create_vec(long double *init_point, long double *terminal_point);
void		compute_vec_len(t_vec *vec);
void		compute_normal_vec(t_vec *vec);
void		normalize_vec(t_vec *vec);

int			is_in_range_f(long double n, long double n_lower,
				long double n_upper);
int			is_in_range_i(int n, int n_lower, int n_upper);

long double	dot(t_vec *vec_1, t_vec *vec_2);
t_vec		*add(t_vec *vec_1, t_vec *vec_2);
void		scale(long double scaler, t_vec *vec);

long double	*quad_eq_solver(long double a,
							long double b,
							long double c,
							long double *disc);
long double	deg_to_rad(long double deg);
long double	rad_to_deg(long double rad);

//	color
t_color			get_rgba(int r, int g, int b, int a);
t_color		update_color_channel(t_color curr_color, t_color new_color, int channel);
t_color		get_color(t_color color, int channel);
t_color		get_r(int rgba);
t_color		get_g(int rgba);
t_color		get_b(int rgba);
t_color		get_a(int rgba);

#endif