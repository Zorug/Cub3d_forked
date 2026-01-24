
# -L - "library path". Diz onde procurar bibliotecas extra (neste caso na pasta: minilibx-linux)
# -l - "link library".
# -I - "include path".
# -o - "output". Gera o executável "test_keys".

# Nome do executável
NAME = test_keys

# Ficheiros fonte
SRCS = test_keys.c

# Compilador e flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Caminhos da MiniLibX
MLX_DIR = ../minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11
MLX_INC = -I$(MLX_DIR)

# Regras
all: $(NAME)

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(MLX_LIB) $(MLX_INC) -o $(NAME)

run: all
	@echo "A correr o $(NAME), pá!"
	./$(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all run clean fclean re