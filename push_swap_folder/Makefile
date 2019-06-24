# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 12:46:06 by uhand             #+#    #+#              #
#    Updated: 2019/06/24 18:51:30 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../push_swap

HEAD = push_swap.h
SRC = push_swap.c ps_atoi.c sorting.c
OBJ = $(addprefix $(OBJPATH)/,$(SRC:.c=.o))

FLAGS = -g #-Wall -Wextra -Werror
LIB = -L ../libft -lft
LIBPATH = ../libft

OBJPATH = ./objects

all: $(NAME)

$(NAME): $(OBJPATH) $(OBJ)
	@make -C $(LIBPATH)
	gcc $(OBJ) -o $(NAME) $(LIB) $(MLIBX)

$(OBJPATH):
	mkdir -p $(OBJPATH)

$(OBJPATH)/%.o: %.c $(HEAD)
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	/bin/rm -rf $(OBJPATH)

fclean: clean
	@make -C $(LIBPATH) fclean
	/bin/rm -f $(NAME)

re: fclean all
