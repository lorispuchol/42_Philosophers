SRCS = 	philo.c \
		free_and_others.c \
		actions.c \

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = gcc
CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

%.o: %.c philo.h Makefile
	$(CC) ${CFLAGS} -c -o $@ $<

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) ${CFLAGS} $(OBJS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: .c.o all clean fclean re