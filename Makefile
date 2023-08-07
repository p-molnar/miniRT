# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/12 14:20:52 by pmolnar       #+#    #+#                  #
#    Updated: 2023/08/07 09:46:53y pmolnar       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
CFLAGS 			= 	-Wall -Werror -Wextra $(addprefix -I, $(INCL))
LDFLAGS			=	-L$(shell brew --prefix glfw)/lib -lglfw -framework Cocoa\
					-framework OpenGL -framework IOKit
CFLAGS			+=	-g # debug
FLAGS			+=	-fsanitize=address
NAME			=	miniRT
INCL			=	inc libft/inc MLX42/include/MLX42

#	DEPENDENDENCIES
LIBFT_DIR		=	libft
LIBFT			=	$(LIBFT_DIR)/libft.a
MLX42_DIR		=	MLX42
MLX42_BUILD_DIR	=	build
MLX42			=	$(MLX42_BUILD_DIR)/libmlx42.a

#	STATUS PRINTER
P_NAME			=	[$(NAME)]
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[1;33m
BOLD			=	\033[1m
DEF				=	\033[0m
SPACE_W 		= 	%-50s
STATUS_W		=	%-10s
P_NAME_W		=	%-10s
STATUS_FMT		=	$(BOLD)$(P_NAME_W) $(DEF) $(STATUS_W) $(SPACE_W)
										
PARSER			=	$(addprefix	parser/,									\
								parser.c									\
						$(addprefix validator/,								\
									input_validator.c						\
									format_validator.c						\
									extension_validator.c						\
									)										\
						$(addprefix	utils/,									\
									parser_utils.c							\
									field_value_derivator.c					\
							$(addprefix	field_parser/,						\
										color_parser.c						\
										coordinate_parser.c					\
										element_parser.c					\
										float_parser.c						\
										)									\
									)										\
								)											\

RENDERER		=	$(addprefix	renderer/,									\
								renderer.c									\
						$(addprefix	shader/,								\
									lighting.c								\
									reflection.c							\
							$(addprefix	color/,								\
										color_ops.c							\
										)									\
									)										\
						$(addprefix	intersections/, 						\
									intersection.c							\
									incident_point_norm.c					\
									sphere.c								\
									plane.c									\
									cylinder.c								\
									)										\
						$(addprefix	transformations/,						\
									transformation.c)						\
								)

UTILS			=	$(addprefix	utils/,										\
								util.c										\
						$(addprefix	free/,									\
									free.c									\
									)										\
						$(addprefix	.helper/,								\
									printer.c								\
									axis.c									\
									)										\
						$(addprefix initialiser/,							\
									ctw_mx.c								\
									init.c									\
									transformation_mx.c						\
									)										\
								)

MATH			=	$(addprefix	math/,										\
						$(addprefix coordinate/, coord_ops.c)				\
						$(addprefix matrix/, 								\
									matrix_ops.c							\
									matrix_ops_2.c)							\
						$(addprefix vector/, 								\
									vector_ops.c							\
									vector_ops_2.c							\
									vector_ops_3.c)							\
						$(addprefix misc/,									\
									quadratic_ops.c							\
									range.c									\
									trigonometry.c)							\
									)

ERROR			=	$(addprefix	error/, 									\
								error.c										\
								)

MLX				=	$(addprefix	mlx/,										\
								key_event.c									\
								)								

SRC				=	main.c													\
					$(PARSER)												\
					$(RENDERER)												\
					$(UTILS)												\
					$(MATH)													\
					$(ERROR)												\
					$(MLX)													\

OBJ_PATH		=	obj/
OBJ				=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))

all:	$(NAME)
	@printf "$(GREEN)$(NAME) is created at $(shell pwd)$(DEF)\n"

$(NAME):	$(LIBFT) $(MLX42) $(OBJ)
	@printf "$(STATUS_FMT)" "$(P_NAME)" "linking" "$(NAME)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(NAME)
	@printf "[$(GREEN)DONE$(DEF)]\n"

$(OBJ_PATH)%.o:	src/%.c
	@mkdir -p $(dir $@)
	@printf "$(STATUS_FMT)" "$(P_NAME)" "compiling" "$<"
	@$(CC) $(CFLAGS) $(MACRO_FLAGS) -c $^ -o $@ 
	@printf "[$(GREEN)DONE$(DEF)]\n"

$(MLX42):	$(MLX42_BUILD_DIR)
	@make -C $(MLX42_BUILD_DIR)

$(MLX42_BUILD_DIR):	$(MLX42_DIR)
	@cmake -S MLX42 -B $(MLX42_BUILD_DIR)
	
$(MLX42_DIR):
	@git submodule update --init --recursive MLX42

$(LIBFT):
	@git submodule update --init --recursive libft
	@make libft.a -C libft

clean:
	@printf "$(STATUS_FMT)" "$(P_NAME)" "removing" "$(OBJ_PATH)"
	@rm -rf $(OBJ_PATH)
	@printf "[$(GREEN)DONE$(DEF)]\n"
	@make clean -C $(LIBFT_DIR)

fclean:
	@printf "$(STATUS_FMT)" "$(P_NAME)" "removing" "$(MLX42_BUILD_DIR)"
	@make clean -C $(MLX42_BUILD_DIR)
	@printf "[$(GREEN)DONE$(DEF)]\n"

	@printf "$(STATUS_FMT)" "$(P_NAME)" "removing" "$(NAME)"
	@rm -f $(NAME)
	@printf "[$(GREEN)DONE$(DEF)]\n"

	@printf "$(STATUS_FMT)" "$(P_NAME)" "removing" "$(OBJ_PATH)"
	@rm -rf $(OBJ_PATH)
	@printf "[$(GREEN)DONE$(DEF)]\n"
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re