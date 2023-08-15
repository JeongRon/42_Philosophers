# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 16:41:08 by jeongrol          #+#    #+#              #
#    Updated: 2023/08/15 16:06:30 by jeongrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror 
# -g3 -fsanitize=thread

RM = rm -f

HEADER	=	philo.h

SRCS	=	main.c \
			set_info.c \
			set_philo.c \
			simulate.c \
			simulate_action.c \
			utils.c \

OBJS	=	$(SRCS:%.c=%.o)


all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:
	make fclean
	make all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

.PHONY:	all clean fclean re bonus