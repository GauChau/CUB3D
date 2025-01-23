NAME = Cub3D
SRCS_ = *.c ./parserr/*.c
SRCS_OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -g

LIBFT_DIR = Libft/
LIBFT = $(LIBFT_DIR)/libft.a

UNAME =$(shell uname -s)
ifeq ($(shell uname -s), Linux)
	INCLUDES = -I/usr/include -Imlx -I$(LIBFT_DIR) -I./includes -I./parser/parser.h
else
	INCLUDES = -I/opt/X11/include -Imlx -I$(LIBFT_DIR)
endif

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname -s), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

all: $(LIBFT) $(MLX_LIB) $(NAME)

ifeq (0, 1)
	.c.o:
	gcc $(CFLAGS) -c -o $@ $< $(INCLUDES)
	$(NAME): $(SRCS_OBJ)
	@echo "Compiling fractol..."
	gcc $(CFLAGS) $(SRCS_) $(INCLUDES) -o $(NAME) $(SRCS_OBJ) $(MLX_FLAGS)
endif

$(MLX_LIB):
	@echo "Making MiniLibX..."
	@make -C $(MLX_DIR)

$(LIBFT):
	@echo "Making Libft.."
	@make -C $(LIBFT_DIR)

$(NAME): $(SRCS_OBJ)
	gcc $(CFLAGS) $(SRCS_) $(INCLUDES) -lm -o $(NAME) $(SRCS_OBJ) $(LIBFT) \
		$(MLX_FLAGS)

clean:
	@echo "Removing .o files"
	rm -f $(SRCS_OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm $(NAME)

re : fclean all

.PHONY: clean all