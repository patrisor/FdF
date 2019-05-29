# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: patrisor <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 02:47:17 by patrisor          #+#    #+#              #
#    Updated: 2019/05/28 21:16:32 by patrisor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= FdF
SRC		= main.c \
		  reader.c \
		  map.c \
		  draw.c \
		  auxiliary_functions.c \
		  window.c \
		  image.c \
		  matrix.c \
		  lineclip.c \
		  controls.c \
		  controls_utils.c \
		  menu.c

# Adds the prefix './obj/' to ever c file compiled as an object
OBJ		= $(addprefix $(OBJDIR), $(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

# mlx library
MLX		= ./minilibx_macos
MLX_LIB	= $(addprefix $(MLX), mlx.a)
MLX_INC	= -I ./minilibx_macos
MLX_LNK	= -L ./minilibx_macos -l mlx -framework OpenGL -framework AppKit

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT), libft.a)
FT_INC	= -I ./libft/includes
FT_LNK	= -L ./libft -l ft

# directories
SRCDIR	= ./src/
OBJDIR	= ./obj/
INCDIR  = ./includes/

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(MLX_LIB):
	make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME) -fsanitize=address -g

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean

re: fclean all
