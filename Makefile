# **************************************************************************** #
#                                   CUB3D                                      #
# **************************************************************************** #

NAME		= cub3D

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iinc -Ilibft
RM			= rm -rf
VALGRIND	= valgrind --track-fds=yes --leak-check=full --show-leak-kinds=definite,indirect,possible
VALGRIND_FULL	= valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all

#==============================================================================#
#                                LIBRARIES                                     #
#==============================================================================#

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx-linux
LDFLAGS		= -L$(MLX_DIR)
LDLIBS		= -lmlx -lXext -lX11 -lm

#==============================================================================#
#                                   PATHS                                      #
#==============================================================================#

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		=	main.c \
				draw.c \
				hooks.c \
				utils.c \
				render.c \
				errors.c \
				validate_map.c \
				initialization.c \
				parsing/parse_map.c \
				parsing/parse_file.c \
				parsing/parse_utils.c \
				parsing/parse_colors.c \
				parsing/parse_textures.c \
				raycast/raycast.c \
				raycast/init_dda.c \
				raycast/draw_minimap.c \


SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                   RULES                                      #
#==============================================================================#

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "\033[0;32mcub3D compiled successfully!\033[0m"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/cub3d.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "Objects removed."

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Executable removed."

re: fclean all

val: $(NAME)
	@$(VALGRIND) ./$(NAME) maps/maptest.cub

val-full: $(NAME)
	@$(VALGRIND_FULL) ./$(NAME) maps/maptest.cub

.PHONY: all clean fclean re val val-full