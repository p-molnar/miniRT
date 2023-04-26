/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:01:05 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/26 14:12:41 by pmolnar       ########   odam.nl         */
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
int			is_in_range_f(long double n, long double n_lower,
				long double n_upper);
int			is_in_range_i(int n, int n_lower, int n_upper);
int			is_valid_number(char *c);

//	error handling
int			error(char *msg, int exit_method, int exit_code);
void		warning(char *msg);

//	renderer
void		render_img(t_data *d);

//	util
t_scn_el	**get_scn_els(t_list *list, enum e_scn_el_type type);

//	math
t_vec		*get_dir_vec(long double *init_point, long double *terminal_point);
long double	*get_normal_vec(t_vec *vec);
long double	dot(t_vec *vec_1, t_vec *vec_2);
long double	*quad_eq_solver(long double a, long double b, long double c,
				long double *disc);
long double	deg_to_rad(long double deg);
long double	rad_to_deg(long double rad);

//	color
int			get_rgba(int r, int g, int b, int a);
t_color		update_color_chanel(t_color curr, t_color new, int channel);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

#endif