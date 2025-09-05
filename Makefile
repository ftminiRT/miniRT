.PHONY : all clean fclean re debug quiet

# Comment next line to show directories
MAKEFLAGS += --no-print-directory
# QUIET = @ -> mutes make cmd in terminal, remove @ to show again
QUIET		=	

CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra -g3 -O3
AR			=	ar -rcs
NAME		= 	miniRT

MLX_PATH	=	./minilibx-linux
MLX			=	minilibx-linux/libmlx_Linux.a
MLXFLAGS	=	$(MLX) -I$(MLX_PATH) -lX11 -lXext

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

INCLUDES	= 	-I$(LIBFT_PATH)/includes \
				-I./includes \
				-I./minilibx-linux

FILES		= 	clean\
				error\
				hit_torus\
				init\
				hit_basics\
				key_hooks\
				mlx_tools\
				mrt_cleaner\
				ray_trace\
				vec3_tools \
				parsing/check_values\
				parsing/init_obj \
				parsing/init_obj_bonus \
				parsing/init_set \
				parsing/ft_atod\
				parsing/parsing_utils \
				parsing/parsing_utils_bonus \
				parsing/parsing \
				light_compute \
				vec3_norm \
				vec3_refs \
				vec3_rot \
				color_tools \
				basics_norm\
				compute_intersections\
				hit_cyl\
				hit_moebius\
				solve_cubic\
				mouse_hooks\
				checkered\
				normal_mapping_utils\
				handle_hooks\
				math_utils_moebius\
				solve_quartic\
				root_compute_utils\
				solve_quadratic\
				textures\
				get_basics_uv\
				get_advanced_uv\
				hit_ring\
				camera_transform\
				ring_normal

SRC_DIR		= 	src/
SRC_FILES	=	$(addsuffix .c, $(FILES))
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

MAIN		=	main.c
OBJ_DIR		= 	obj/
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_MAIN	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_DIR)$(MAIN))


$(NAME) : $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJ) $(OBJ_MAIN)
	$(QUIET) $(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(OBJ_MAIN) -L$(LIBFT_PATH) -lft $(MLXFLAGS) -lm -o $(NAME)

$(MLX):
	make -C $(MLX_PATH)

$(LIBFT):
	$(QUIET) make all -C $(LIBFT_PATH) 

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(QUIET) $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR) : 
	$(QUIET) mkdir -p $(OBJ_DIR)
	$(QUIET) mkdir -p $(OBJ_DIR)/parsing


all : $(NAME)
	@ echo "minirt is ready !"

clean :
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_PATH)

clean_mlx:
	rm -rf $(MLX_PATH)

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re : fclean all
