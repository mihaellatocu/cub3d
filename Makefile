NAME = cub
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
OBJ_F = ./obj

SRC = src/parsing/main.c src/parsing/get_next_line.c src/parsing/get_next_line_utils.c \
		src/parsing/parse_colours.c src/parsing/create_map.c src/parsing/check_map.c\
		src/parsing/check_texture.c \
		src/parsing/free.c \
		src/exec/execution.c \
		
		

###################### LIBRARIES ###################
LIBFT = lib
LIBFT_LIB = $(LIBFT)/libft.a

MINIX11 = ./minilibx-linux
MINIX11_LIB = $(MINIX11)/libmlx_Linux.a
MINIX11_FLAGS = -lXext -lX11

OBJ = $(SRC:src/%.c=$(OBJ_F)/%.o)

############################ RULES ######################################

all: $(NAME) 

$(NAME): $(OBJ)
	@make -C $(MINIX11)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_LIB) $(MINIX11_LIB) $(MINIX11_FLAGS)
#-Iget_next_line.h


$(OBJ_F)/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT) clean
	@make -C $(MINIX11) clean
	$(RM) $(OBJ) $(OBJ_F)

fclean: clean
	@make -C $(LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.Phony: clean fclean re all






