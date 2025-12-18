NAME        = miniRT

LIBRARY_DIR = ./minilibx-linux
LIBFT_DIR   = ./libft

CC          = cc
# CFLAGS      = -Wall -Wextra -Werror

INCLUDES    = -I. -I./libft -I$(LIBRARY_DIR)

MLX_FLAGS   = -L$(LIBRARY_DIR) -lmlx -lXext -lX11 -lm
LIBS        = -L$(LIBFT_DIR) -lft

RM          = rm -f

SRCS        = main.c \
			  init.c \
			  vector/vec_util1.c \
			  vector/vec_util2.c \
			  vector/vec_util3.c \
			  hit/normal.c \
			  hit/hit_sphere.c \
			  hit/hit_plane.c \
			  hit/hit_cylinder.c \
			  hit/hit_cylinder/cylinder.c \
			  hit/hit_cylinder/cap.c \
			  hit/hit.c \
			  ray/phong_lighting.c \
			  ray/ray.c \
              parse/read_value.c \
              parse/parse.c \
              parse/parse_shape.c \
              parse/parse_util.c \
              parse/object_list.c \
              parse/check_value.c \
              readline/cm_readline.c \
              readline/cm_readline_utils.c \
			  event/key_event.c \
			  event/mouse_event.c \
			  event/rotation.c
OBJS        = $(SRCS:.c=.o)
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re