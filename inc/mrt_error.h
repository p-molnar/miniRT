/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_error.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 21:01:01 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/26 13:13:42 by pmolnar       ########   odam.nl         */
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

# define FMT_E_AMB_LIGHT "Required line format: A <light intensity> <color>"
# define FMT_E_PNT_LIGHT "Required line format: L <coordinate> \
<light intensity> <color>"
# define FMT_E_DIR_LIGHT "Required line format: DL <coordinate> \
<light intensity> <color>"
# define FMT_E_CAM "Required line format: C <coordinate> <coordinate> <FOV>"
# define FMT_E_TGCAM "Required line format: TC <coordinate> <coordinate> <FOV>"
# define FMT_E_SPHERE "Required line format: sp <coordinate> <diameter> \
<color> <specular factor> <reflection factor>"
# define FMT_E_PLANE "Required line format: pl <coordinate> <coordinate> \
<color> <specular factor> <reflection factor>"
# define FMT_E_CYLINDER "Required line format: cy <coordinate> <coordinate> \
<diameter> <height> <color> <specular factor> <reflection factor>"
#endif