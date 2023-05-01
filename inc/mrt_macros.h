/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_macros.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:52:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/01 13:06:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_MACROS_H
# define MRT_MACROS_H
# define CANVAS_W 800
# define CANVAS_H 800
# define INF 99999

enum e_range
{
	MIN,
	MAX,
	RANGE_SIZE,
};

enum	e_error_handler
{
	EXIT = 1,
	RETURN = 2,
};

enum	e_vec_params
{
	CO,
	D,
	O,
	P,
	N,
	PARAM_SIZE,
};

enum	e_coord
{
	X,
	Y,
	Z,
	COORD_SIZE,
};

enum	e_color
{
	A,
	B,
	G,
	R,
};

enum	e_scn_el_type
{
	TYPE_UNDEF = 0,
	AMB_LIGHT = 1 << 0,
	CAM = 1 << 1,
	LIGHT = 1 << 2,
	DIR_LIGHT = 1 << 3,
	SPHERE = 1 << 4,
	PLANE = 1 << 5,
	CYLYNDER = 1 << 6,
};

enum	e_groupped_el
{
	G_LIGHT = AMB_LIGHT | LIGHT,
	G_CAM = CAM,
	G_OBJS = SPHERE | PLANE | CYLYNDER,
};

enum	e_scn_el_member_flags
{
	F_COORD = 1 << 0,
	F_N_VEC = 1 << 1,
	F_DMETER = 1 << 2,
	F_HEIGHT = 1 << 3,
	F_FOV = 1 << 4,
	F_INTENSITY = 1 << 5,
	F_COLOR = 1 << 6,
};

#endif