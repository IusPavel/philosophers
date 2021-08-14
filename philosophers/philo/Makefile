NAME   :=	philo
SRC    :=	philosophers.c ft_utils.c philo_loop.c waiter_loop.c
OBJ    :=	$(SRC:.c=.o)
HDR    :=	philosophers.h
CC     :=	gcc
CFLAGS :=	-Wall -Wextra -Werror -MMD
all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus:

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

include		$(wildcard *.d)

clean:
			rm -rf *.o *.d

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
