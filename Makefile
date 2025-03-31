# Reset terminal color at end
RESET=\033[0m
GREEN=\033[1;32m
RED=\033[1;31m
YELLOW=\033[1;33m
CYAN=\033[1;36m

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I./minilibx-linux
RM = rm -rf
OBJDIR = obj

SRC = \
	src/parsing/main.c \
	src/parsing/check_map.c \
	src/parsing/check_texture.c \
	src/parsing/map_parse_utils.c \
	src/parsing/parse_colours.c \
	src/parsing/parsing_utils.c \
	src/parsing/free.c \
	src/exec/game_init.c \
	src/exec/hooks.c \
	src/exec/movements.c \
	src/raycast/img_init.c \
	src/raycast/minimap_rendering.c \
	src/raycast/raycasting.c \
	src/raycast/raycasting_utils.c \
	src/raycast/rendering_core.c

LIBFT = lib
LIBFT_LIB = $(LIBFT)/libft.a

MINIX11 = ./minilibx-linux
MINIX11_LIB = $(MINIX11)/libmlx_Linux.a
MINIX11_FLAGS = -lXext -lX11

OBJ = $(SRC:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo -e "$(CYAN)[BUILD]$(RESET) Compiling dependencies..."
	@make -C $(MINIX11)
	@make -C $(LIBFT)
	@echo -e "$(CYAN)[LINK]$(RESET) Linking executable..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_LIB) $(MINIX11_LIB) $(MINIX11_FLAGS) -lm
	@echo -e "$(GREEN)[SUCCESS]$(RESET) Build completed: $(NAME)"

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(@D)
	@echo -e "$(YELLOW)[COMPILE]$(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo -e "$(RED)[CLEAN]$(RESET) Cleaning object files..."
	@make -C $(LIBFT) clean
	@make -C $(MINIX11) clean
	@$(RM) $(OBJ) $(OBJDIR)

fclean: clean
	@echo -e "$(RED)[FCLEAN]$(RESET) Removing binary..."
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all