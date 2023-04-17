/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_data_struct.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:06:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/17 13:54:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_DATA_STRUCT_H
# define MRT_DATA_STRUCT_H

# include <libft.h>

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

typedef struct s_coord_3d
{
	int	x;	
	int	y;	
	int	z;	
}	t_coord_3d;

// typedef struct s_cam
// {
// 	int				type;
// 	t_coord_3d		coord;
// 	t_coord_3d		norm_vec;
// 	unsigned int	fov;
// }	t_cam;

// typedef struct s_amb_light
// {
// 	int				type;
// 	unsigned int	brightness;
// 	t_color			color;
// }	t_amb_light;

// typedef struct s_sphere
// {
// 	int				type;
// 	t_coord_3d		coord;
// 	int				diamtr;
// 	t_color			color;
// }	t_sphere;

// typedef struct s_plane
// {
// 	int				type;
// 	t_coord_3d		coord;
// 	t_coord_3d		norm_vec;
// 	t_color			color;
// }	t_plane;

// typedef struct s_cylinder
// {
// 	int				type;
// 	t_coord_3d		coord;
// 	t_coord_3d		norm_vec;
// 	int				diamtr;
// 	int				height;
// 	t_color			color;
// }	t_cylinder;

// typedef struct s_light
// {	
// 	int				type;
// 	t_coord_3d		pos;
// 	unsigned int	brightness;
// 	t_color			color;
// }	t_light;

typedef struct s_scn_el
{
	int				type;
	float			coord[3];
	float			norm_vec[3];
	float			diameter;
	float			height;
	float			fov;
	float			brightness;
	unsigned int	color[3];
}	t_scn_el;

typedef struct s_scn
{
	t_list	*els;
}	t_scn;

#endif