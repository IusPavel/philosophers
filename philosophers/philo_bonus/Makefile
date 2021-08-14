NAME   :=	philo_bonus
SRC    :=	philosophers_bonus.c ft_utils_bonus.c \
			philo_loop_bonus.c waiter_loop_bonus.c
OBJ    :=	$(SRC:.c=.o)
HDR    :=	philosophers_bonus.h
CC     :=	gcc
CFLAGS :=	-Wall -Wextra -Werror -MMD

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus:		all

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

include		$(wildcard *.d)

clean:
			rm -rf *.o *.d

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
