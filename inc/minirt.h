/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:01:05 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/24 22:55:47 by pmolnar       ########   odam.nl         */
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
void		parse_coordinates(double *coord, char *input);
void		parse_norm_vec(double *coord, char *input);
void		parse_double(double *f, char *input);
void		parse_range(double *f, char *input, double n_lower, double n_upper);
void		parse_color(t_color *color, char *input, int n_lower, int n_upper);

//	free
void		free_arr(void **arr);

//	parser utils
int			get_arr_size(char **arr);
int			is_in_range_f(double n, double n_lower, double n_upper);
int			is_in_range_i(int n, int n_lower, int n_upper);
int			is_valid_number(char *c);

//	error handling
int			error(char *msg, int exit_method, int exit_code);
void		warning(char *msg);

//	renderer
void		render_img(t_data *d);

//	util
t_scn_el	**get_scn_els(t_list *list, t_el_type type);

//	math
t_vec		*get_dir_vec(double *init_point, double *terminal_point);
double		dot(t_vec *vec_1, t_vec *vec_2);

//	color
int			get_rgba(int r, int g, int b, int a);
t_color		update_color_chanel(t_color curr, t_color new, int channel);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

#endif