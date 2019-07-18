# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 12:47:56 by uhand             #+#    #+#              #
#    Updated: 2019/07/18 17:38:21 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../checker

HEAD = checker.h
SRC = checker.c service_fnctns.c ps_atoi.c exec_commands.c exec_commands_2.c \
visualizer.c visualizer_2.c visualizer_3.c visualizer_4.c
OBJ = $(addprefix $(OBJPATH)/,$(SRC:.c=.o))

FLAGS = -Wall -Wextra -Werror
LIB = -L ../libft -lft
LIBPATH = ../libft

MLIBX = -L  ../minilibx -lmlx -framework OpenGL -framework AppKit
MLIBXPATH = ../minilibx
OBJPATH = ./objects

all: $(NAME)

$(NAME):  $(OBJPATH) $(OBJ)
	@make -C $(LIBPATH)
	@make -C $(MLIBXPATH)
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIB) $(MLIBX)

$(OBJPATH):
	mkdir -p $(OBJPATH)

$(OBJPATH)/%.o: %.c $(HEAD)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	@make -C $(MLIBXPATH) clean
	/bin/rm -rf $(OBJPATH)

fclean: clean
	@make -C $(LIBPATH) fclean
	@make -C $(MLIBXPATH) fclean
	/bin/rm -f $(NAME)

re: fclean all
