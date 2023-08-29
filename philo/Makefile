# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/19 21:46:42 by mrizakov          #+#    #+#              #
#    Updated: 2023/08/24 19:02:56 by mrizakov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

SRC = philos_exit.c philos.c philos_utils.c philos_func.c philos_func_2.c philos_monitor.c philos_init.c philos_time.c philos_input.c
EXECUTABLE = philo

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CFLAGS) $(SRC) -o $@
	
fclean:
	rm -f $(EXECUTABLE)

re:fclean all