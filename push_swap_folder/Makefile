# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 12:46:06 by uhand             #+#    #+#              #
#    Updated: 2019/07/17 14:00:57 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../push_swap

HEAD = push_swap.h
SRC = push_swap.c ps_atoi.c sorting.c copy_linked_stack.c command_generator.c \
commands.c commands_2.c commands_3.c command_generator_2.c service_functions.c \
command_generator_3.c stack_normalise.c stack_normalise_2.c \
stack_normalise_3.c run_rev_drums.c run_rev_drums_2.c get_sequence.c \
get_sequence_2.c file_writing.c
OBJ = $(addprefix $(OBJPATH)/,$(SRC:.c=.o))

FLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
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
