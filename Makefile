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
init\
key_hooks

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
