# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaach <amaach@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 14:50:01 by amaach            #+#    #+#              #
#    Updated: 2021/01/22 14:28:27 by amaach           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


FLAGS =  -Wall -Wextra -Werror

MLX = -I /usr/local/include -L /usr/local/lib/ -lmlx

FRAMEWORKS = -framework OpenGl -framework Appkit


EXEC = cub3D

SRC =  ./outils/ft_isdigit.c ./outils/ft_putstr_fd.c ./outils/ft_strchr.c ./outils/ft_strtrim.c\
		./outils/ft_strjoin.c ./outils/ft_strrev.c ./outils/get_next_line.c \
		./other_outils/wall_projecting.c ./outils/ft_atoi.c ./outils/ft_putchar_fd.c \
		./outils/ft_split.c ./outils/ft_strdup.c ./outils/ft_strlen.c \
		./outils/ft_substr.c main.c ./read_map/read_maps.c ./read_map/help_map.c \
		./read_map/help_config.c ./read_map/help_error.c ./read_map/help_paco.c \
		./read_map/help_spaces.c ./raycasting/ray_casting.c ./raycasting/help_casting.c \
		./helpcub/cub3d.c ./helpcub/help_cub.c ./helpcub/otherhelp.c ./other_outils/sprite.c \
		./other_outils/save.c
NAME = lib.a
OBJ = *.o

all:	$(NAME)

$(NAME) :
	gcc $(FLAGS) -c $(SRC)
	ar -rc  $(NAME) $(OBJ)
	ranlib $(NAME)
	gcc $(FLAGS) $(MLX) $(NAME) $(FRAMEWORKS) -o $(EXEC)

bonus : $(SRC)

clean:
	rm -f $(OBJ) $(NAME)

fclean:	clean
	rm -f $(EXEC)

re:		fclean all
