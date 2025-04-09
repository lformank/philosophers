# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lformank <lformank@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 16:20:21 by lformank          #+#    #+#              #
#    Updated: 2025/04/09 16:41:29 by lformank         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
SUBJS = philo.c init.c utils.c
OBJS = philo.o init.o utils.o

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