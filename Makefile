NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

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
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -pthread

.PHONY:	all clean fclean re bonus