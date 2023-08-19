# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrizakov <mrizakov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/19 21:46:42 by mrizakov          #+#    #+#              #
#    Updated: 2023/08/19 23:02:41 by mrizakov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra 

SRC = philos_exit.c philos.c philos_utils.c philos_func.c philos_monitor.c philos_init.c philos_time.c philos_input.c
OBJ = $(SRC:.c=.o)
INCLUDES = philos.h
EXECUTABLE = philos

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -g3 -pthread -o $@

$(EXECUTABLE)_sanitize: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -g3 -pthread -fsanitize=thread -o $(EXECUTABLE)

name:
	@echo "Building $(EXECUTABLE)"

name_sanitize:
	echo "Building $(EXECUTABLE) with fsanitize"

clean:
	rm -f $(OBJ)
	
fclean:clean
	rm -f $(EXECUTABLE)
