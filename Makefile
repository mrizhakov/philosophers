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
CFLAGS_W_FSANITIZE = -Wall -Werror -Wextra -pthread -g -fsanitize=address
CFLAGS = -Wall -Werror -Wextra


SRC = philos_exit.c philos.c philos_utils.c philos_func.c philos_monitor.c philos_init.c philos_time.c philos_input.c
OBJ = $(SRC:.c=.o)
INCLUDES = philos.h
EXECUTABLE = philos

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(EXECUTABLE)_sanitize: $(OBJ)
##	$(CC) $(CFLAGS) $(OBJ) -g3  -o $(EXECUTABLE)_sanitize
	$(CC) $(CFLAGS_W_FSANITIZE) $(SRC) -o $(EXECUTABLE)_sanitize

##	$(CC) $(CFLAGS) $(OBJ) -g3 -pthread -fsanitize=address -fsanitize=thread -o $(EXECUTABLE)_sanitize

name:
	@echo "Building $(EXECUTABLE)"

name_sanitize:
	echo "Building $(EXECUTABLE) with fsanitize"

clean:
	rm -f $(OBJ)
	
fclean:clean
	rm -f $(EXECUTABLE) $(EXECUTABLE)_sanitize

re:fclean clean
