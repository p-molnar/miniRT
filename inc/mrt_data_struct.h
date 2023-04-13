/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_data_struct.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:06:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/13 13:08:07 by pmolnar       ########   odam.nl         */
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

typedef struct s_cam
{
	char			*type;
	t_coord_3d		pos;
	t_coord_3d		vec;
	unsigned int	fov;
}	t_cam;

typedef struct s_amb_light
{
	char			*type;
	unsigned int	brightness;
	t_color			color;
}	t_amb_light;

typedef struct s_sphere
{
	char			*type;
	t_coord_3d		pos;
	int				diamtr;
	t_color			color;
}	t_sphere;

typedef struct s_plane
{
	char			*type;
	t_coord_3d		pos;
	t_coord_3d		vec;
	t_color			color;
}	t_plane;

typedef struct s_cylinder
{
	char			*type;
	t_coord_3d		pos;
	t_coord_3d		vec;
	int				diamtr;
	int				height;
	t_color			color;
}	t_cylinder;

typedef struct s_light
{
	char			*type;
	t_coord_3d		pos;
	unsigned int	brightness;
	t_color			color;
}	t_light;

typedef struct s_scn
{
	t_list	*els;
}	t_scn;

#endif