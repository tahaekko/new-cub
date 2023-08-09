# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 17:25:24 by msamhaou          #+#    #+#              #
#    Updated: 2023/08/09 14:53:28 by msamhaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D
CC = cc
CFLAGS = #-fsanitize=address
HEADER = cub3d.h

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -lmlx -lm -lbsd -lX11 -lXext
	MLX_DIR = minilibx-linux/
	MLX_LINK = -L/usr/lib/
	MLX_INC = -I/usr/include
else
	MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -L /Users/msamhaou/MLX42/build
	MLX_DIR =
	MLX_LINK =
	MLX_INC = -I /usr/local/include -I /Users/msamhaou/MLX42/include/MLX42
endif


OBJ_DIR = obj/

#*****************GNL*****************

GNL_SRC = gnl.c       gnl_tools.c
GNL_DIR = GNL/
GNL_OBJ_FILE = $(GNL_SRC:.c=.o)
GNL_OBJ = $(addprefix $(OBJ_DIR), $(GNL_OBJ_FILE))

#*****************GARB*****************

GARB_SRC = col.c
GARB_DIR = garbage/
GARB_OBJ_FILE = $(GARB_SRC:.c=.o)
GARB_OBJ = $(addprefix $(OBJ_DIR), $(GARB_OBJ_FILE))

#****************LIBFT****************
LIBFT_SRC =	ft_strlen.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_strjoin.c ft_strdup.c ft_memcpy.c ft_strlcpy.c\
			ft_itoa.c ft_strncmp.c ft_substr.c ft_atoi.c ft_split.c ft_strchr.c
LIBFT_DIR =	libft/
LIBFT_OBJ_FILE = $(LIBFT_SRC:.c=.o)
LIBFT_OBJ = $(addprefix $(OBJ_DIR), $(LIBFT_OBJ_FILE))


#*****************SRC*****************
SRC_DIR = src/
SRC = ft_init.c        ft_tool.c        ft_vector_draw.c libx_tools.c     main.c	ft_parse.c\
		ft_draw.c	ft_gsplit.c	ft_print_err.c ft_gsubstr.c ft_gatoi.c ft_map_list.c	ft_map_chek.c
FSRC = $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(SRC:.c=.o)
FOBJ = $(addprefix $(OBJ_DIR), $(OBJ))

all : $(NAME)

$(NAME): $(OBJ_DIR) $(FOBJ) $(LIBFT_OBJ) $(GNL_OBJ) $(GARB_OBJ)
	${CC} $(CFLAGS) -o $(NAME) $(FOBJ) $(LIBFT_OBJ) $(GNL_OBJ) $(GARB_OBJ) $(MLX_LINK) $(MLX_FLAGS)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(LIBFT_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(MLX_INC) -Iinclude/

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(MLX_INC) -Iinclude/

$(OBJ_DIR)%.o : $(GNL_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(MLX_INC) -Iinclude/

$(OBJ_DIR)%.o : $(GARB_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(MLX_INC) -Iinclude/

prog : all
	./$(NAME)
clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -rf $(NAME)
re : fclean all
