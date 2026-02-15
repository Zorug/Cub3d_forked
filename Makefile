# **************************************************************************** #
#                                   CUB3D                                      #
# **************************************************************************** #

NAME		= cub3D

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Libraries
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= ./minilibx-linux
MLX_FLAGS	= -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#
# Folders and Files
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= inc

SRCS		= $(SRC_DIR)/main.c \
			$(SRC_DIR)/leaks.c \
			$(SRC_DIR)/hooks.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/draw.c \
			#$(SRC_DIR)/utils/error_handling.c

#FILES			= 	main.c \

#SRCS			= 	$(addprefix $(SRC_PATH)/, $(FILES)) \
					#$(addprefix $(SRC_PATH)/builtins/, $(BUILTINS))

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Terminal colors
GREEN		= \033[0;32m
RESET		= \033[0m

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#
# Main Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	#@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)cub3D compiled successfully!$(RESET)"

# Libft Compilation 
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Rule for objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	#@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@
	@$(CC) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Cleanup
clean:
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "Objects removed."

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Executable and libraries removed."

re: fclean all

# Bonus Rule [cite: 38]
bonus: all
	@echo "$(GREEN)Bonus included (if implemented in _bonus.c files)$(RESET)"

.PHONY: all clean fclean re bonus