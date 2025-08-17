# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lformank <lformank@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:20:21 by lformank          #+#    #+#              #
#    Updated: 2025/08/17 21:53:04 by lformank         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=thread
RM = rm -f
SUBJS = philo.c init.c utils.c routine.c conditions.c death_routine.c \
		get_set.c
OBJS = philo.o init.o utils.o routine.o conditions.o death_routine.o \
		get_set.o

all: philo

%.o: %.c philo.h
	$(CC) $(CFLAGS) $(SUBJS) -c

philo: $(OBJS) 
	$(CC) $(CFLAGS) $(SUBJS) -o philo

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) philo

re: fclean all

.PHONY: all clean fclean re