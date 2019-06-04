# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 12:48:29 by uhand             #+#    #+#              #
#    Updated: 2019/05/28 15:48:26 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME = push_swap checker

all:
	@make -C ./push_swap_folder
	@make -C ./checker_folder

clean:
	@make -C ./push_swap_folder clean
	@make -C ./checker_folder clean

fclean: clean
	@make -C ./push_swap_folder fclean
	@make -C ./checker_folder fclean

re: fclean all
