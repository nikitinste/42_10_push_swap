# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 12:46:06 by uhand             #+#    #+#              #
#    Updated: 2019/06/30 18:41:44 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../push_swap

HEAD = push_swap.h
SRC = push_swap.c ps_atoi.c sorting.c copy_linked_stack.c command_generator.c \
commands.c commands_2.c commands_3.c command_generator_2.c \
command_generator_3.c stack_normalise.c stack_normalise_2.c
OBJ = $(addprefix $(OBJPATH)/,$(SRC:.c=.o))

FLAGS = -g #-fsanitize=address -Wall -Wextra -Werror
LIB = -L ../libft -lft
LIBPATH = ../libft

OBJPATH = ./objects

all: $(NAME)

$(NAME): $(OBJPATH) $(OBJ)
	@make -C $(LIBPATH)
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIB) $(MLIBX)

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
