/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_macros.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:52:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/21 21:14:33 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_MACROS_H
# define MRT_MACROS_H
# define WIDTH 500
# define HEIGHT 500
# define VIEWPORT_W 500
# define VIEWPORT_H 500

enum	e_error_handler
{
	EXIT = 1,
	RETURN = 2,
};

enum	e_scn_el_type
{
	TYPE_UNDEF,
	AMB_LIGHT,
	LIGHT,
	CAM,
	SPHERE,
	PLANE,
	CYLYNDER
};

enum	e_scn_el_member_flags
{
	F_COORD = 1 << 0,
	F_VEC = 1 << 1,
	F_DMETER = 1 << 2,
	F_HEIGHT = 1 << 3,
	F_FOV = 1 << 4,
	F_BRIGHT = 1 << 5,
	F_COLOR = 1 << 6,
};

#endif