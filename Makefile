# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pmolnar <pmolnar@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/12 14:20:52 by pmolnar       #+#    #+#                  #
#    Updated: 2023/04/13 13:10:51 by pmolnar       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC 				= 	gcc
# CFLAGS 			= 	-Wall -Werror -Wextra $(addprefix -I, $(INCL))
CFLAGS 			= 	$(addprefix -I, $(INCL))
LDFLAGS			=	-lglfw -L$(shell brew --prefix glfw)/lib
CFLAGS			+=	-g # debug
# CFLAGS			+=	-fsanitize=address
NAME			=	minirt
INCL			=	inc libft/inc MLX42/include/MLX42

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
SPACE_W 		= 	%-40s
STATUS_W		=	%-10s
P_NAME_W		=	%-10s
STATUS_FMT		=	$(BOLD)$(P_NAME_W) $(DEF) $(STATUS_W) $(SPACE_W)

#	PARSER
PARSER			=	$(addprefix	parser/,									\
								parser.c									\
								)

ERROR			=	$(addprefix	error/, 									\
								error.c										\
								)

#	SOURCE FILES
SRC				=	main.c $(PARSER) $(ERROR)

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
	@$(CC) $(CFLAGS) -c $^ -o $@ 
	@printf "[$(GREEN)DONE$(DEF)]\n"

$(MLX42):	$(MLX42_DIR)
	@make -C $(MLX42_BUILD_DIR)

$(MLX42_DIR):
	@git submodule update --init --remote --recursive MLX42
	@cmake -S MLX42 -B $(MLX42_BUILD_DIR)
	

$(LIBFT):
	@git submodule update --init --remote --recursive libft
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