/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:01:05 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/17 13:55:53 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mrt_data_struct.h>

//	parser
void	parse_scene(t_scn *scn, int argc, char *argv[]);
void	parse_elements(t_scn_el *el, char **input, unsigned int flags);
void	parse_type_identifier(t_scn_el *el, char *line);

//	element parser
void	parse_coordinates(float *coord, char *input);
void	parse_norm_vec(float *coord, char *input);
void	parse_float(float *f, char *input);
void	parse_range(float *f, char *input, float n_lower, float n_upper);
void	parse_color(unsigned int *color, char *input, int n_lower, int n_upper);

//	free
void	free_arr(char **arr);

//	parser utils
int		get_arr_size(char **arr);
int		is_in_range_f(float n, float n_lower, float n_upper);
int		is_in_range_i(int n, int n_lower, int n_upper);
int		is_valid_number(char *c);

//	error handling
int		error(char *msg, int exit_method, int exit_code);

#endif