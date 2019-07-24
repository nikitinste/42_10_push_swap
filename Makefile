# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/28 12:48:29 by uhand             #+#    #+#              #
#    Updated: 2019/07/24 17:24:34 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
