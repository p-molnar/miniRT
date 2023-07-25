/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_error.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:01:01 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/25 16:43:13 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_ERROR_H
# define MRT_ERROR_H
# include <errno.h>
# include <string.h>

# define CAM_REQUIRED "Required element: Camera"
# define CAM_INSIDE_OBJ "Camera can't be inside an object"
# define DUPLICATE_EL "Duplicate element"
# define REQUIRED_ARGC "Expected argument count: 2"
# define OUT_OF_RANGE "Value out of range"
# define INVALID_NUM "Invalid number representation"
# define WRONG_SEP "Wrong value separation / incomplete set of values"
# define NULL_PTR "NULL Pointer error"
# define WRONG_EL "Element must be of type: A, L, DL, C, TC, sp, pl, cy"

#endif