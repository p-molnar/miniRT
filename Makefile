# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/12 14:20:52 by pmolnar       #+#    #+#                  #
#    Updated: 2023/07/25 23:23:28 by pmolnar       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
CFLAGS 			= 	-Wall -Werror -Wextra $(addprefix -I, $(INCL))
LDFLAGS			=	-L$(shell brew --prefix glfw)/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
MACRO_FLAGS		=	-DRECURSIVE_DEPTH=$(RECURSIVE_DEPTH)
CFLAGS			+=	-g # debug
# CFLAGS			+=	-fsanitize=address
NAME			=	minirt
INCL			=	inc libft/inc MLX42/include/MLX42

#	ENV VAR
RECURSIVE_DEPTH	?=	0

#	DEPENDENDENCIES
LIBFT_DIR		=	libft
LIBFT			=	$(LIBFT_DIR)/libft.a
MLX42_DIR		=	MLX42
MLX42_BUILD_DIR	=	build
MLX42			=	$(MLX42_BUILD_DIR)/libmlx42.a

# PRINT FORMATTING
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

#	PARSER
INITAILISER		=	$(addprefix initialiser/,								\
								ctw_mx.c									\
								init.c										\
								transformation_mx.c)

PARSER			=	$(addprefix	parser/,									\
								parser.c									\
								parser_utils.c								\
								$(EL_PARSER)								\
								input_validator.c							\
								)

EL_PARSER		=	$(addprefix	element_parser/,							\
								color_parser.c								\
								coordinate_parser.c							\
								element_parser.c							\
								float_parser.c								\
								)

ELEMENTS		=	$(addprefix	elements/, 									\
								sphere.c									\
								plane.c										\
								cylinder.c									\
								)


ERROR			=	$(addprefix	error/, 									\
								error.c										\
								)

FREE			=	$(addprefix	free/,										\
								free.c										\
								)

LIGHTING		=	$(addprefix	lighting/,									\
								lighting.c									\
								specular_lighting.c							\
								)

RENDERER_COLOR	=	$(addprefix	color/,										\
								render_color.c								\
								)

TRANSFORMATION	=	$(addprefix	transformations/,							\
								transformation.c)							\

RENDERER		=	$(addprefix	renderer/,									\
								renderer.c									\
								renderer_util.c								\
								$(LIGHTING)									\
								$(RENDERER_COLOR)							\
								$(ELEMENTS)									\
								$(SHADOW)									\
								$(TRANSFORMATION)							\
								)

UTIL			=	$(addprefix	util/,										\
								util.c										\
								)

MATH			=	$(addprefix	math/,										\
						$(addprefix coordinate/, coord_ops.c)				\
						$(addprefix matrix/, 								\
							matrix_ops.c									\
							matrix_ops_2.c)									\
						$(addprefix vector/, 								\
							vector_ops.c									\
							vector_ops_2.c									\
							vector_ops_3.c)									\
						$(addprefix misc/,									\
							quadratic_ops.c									\
							range.c											\
							trigonometry.c)									\
								)

COLOR			=	$(addprefix	color/,										\
								color_ops.c									\
								)

HELPER			=	$(addprefix	helper/,									\
								printer.c									\
								axis.c										\
								)
#	SOURCE FILES
SRC				=	main.c													\
					$(INITAILISER)											\
					$(PARSER)												\
					$(ERROR)												\
					$(FREE)													\
					$(RENDERER)												\
					$(UTIL)													\
					$(COLOR)												\
					$(MATH)													\
					$(HELPER)												\

OBJ_PATH		=	obj/
OBJ				=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))

all:	$(NAME)
	@printf "$(GREEN)$(NAME) is created at $(shell pwd)$(DEF)\n"

$(NAME):	$(LIBFT) $(MLX42) $(OBJ)
	@printf "$(STATUS_FMT)" "$(P_NAME)" "building" "$(NAME)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(NAME)
	@printf "[$(GREEN)DONE$(DEF)]\n"

$(OBJ_PATH)%.o:	src/%.c
	@mkdir -p $(dir $@)
	@printf "$(STATUS_FMT)" "$(P_NAME)" "building" "$<"
	@$(CC) $(CFLAGS) $(MACRO_FLAGS) -c $^ -o $@ 
	@printf "[$(GREEN)DONE$(DEF)]\n"

$(MLX42):	$(MLX42_BUILD_DIR)
	@make -C $(MLX42_BUILD_DIR)

$(MLX42_BUILD_DIR):
	# @git submodule update --init --remote --recursive MLX42
	@cmake -S MLX42 -B $(MLX42_BUILD_DIR)
	

$(LIBFT):
	# @git submodule update --init --remote --recursive libft
	@make libft.a -C libft

clean:
	@printf "$(STATUS_FMT)" "$(P_NAME)" "removing" "$(OBJ_PATH)"
	@rm -rf $(OBJ_PATH)
	@printf "[$(GREEN)DONE$(DEF)]\n"
	@make clean -C $(LIBFT_DIR)

fclean:	
	@printf "$(STATUS_FMT)" "$(P_NAME)" "removing" "$(NAME)"
	@rm -f $(NAME)
	@printf "[$(GREEN)DONE$(DEF)]\n"

	@printf "$(STATUS_FMT)" "$(P_NAME)" "removing" "$(OBJ_PATH)"
	@rm -rf $(OBJ_PATH)
	@printf "[$(GREEN)DONE$(DEF)]\n"
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re