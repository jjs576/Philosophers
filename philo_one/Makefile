# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjoo <jjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/02 16:57:38 by jjoo              #+#    #+#              #
#    Updated: 2021/06/07 13:27:12 by jjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_one
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	srcs/init.c srcs/main.c srcs/routine.c srcs/utils.c srcs/run.c
INCS	=	-I includes
OBJS	=	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCS)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
