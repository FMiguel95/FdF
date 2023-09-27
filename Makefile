NAME = fdf

SRCS_LIST = fdf.c parse_map.c fdf_utils.c events.c display.c mathf.c actions.c \
			draw_line.c initializations.c
SRCS_DIR = srcs/
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

LIBFT_DIR = libft/
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

LIBMLX_DIR = minilibx/
LIBMLX = $(addprefix $(LIBMLX_DIR), libmlx.a)

CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx -lX11 -lXext -lm -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBMLX):
	make -C $(LIBMLX_DIR)

clean:
	$(RM) $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(LIBMLX_DIR)

re: fclean all
