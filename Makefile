# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/19 21:46:42 by mrizakov          #+#    #+#              #
#    Updated: 2023/08/19 21:59:22 by mrizakov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -pthread

SRC = philos_exit.c philos.c philos_utils.c philos_func.c philos_monitor.c philos_init.c philos_time.c philos_input.c
OBJ = $(SRC:.c=.o)
INCLUDES = philos.h
EXECUTABLE = philos

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
##	cc $(SRC) -g3 -pthread -fsanitize=thread -o philos

name:
	@echo "Building $(EXECUTABLE)"

clean:
	rm -f $(OBJ)
	
fclean:clean
	rm -f $(EXECUTABLE)

re: fclean all
