NAME = fract_ol

CFILES = main.c mandelbrot.c

OBJS := $(CFILES:.c=.o)

CC = cc

LIBFTDIR = 42-libft/
MLIBXDIR = minilibx-linux/

LIBFT := ${LIBFTDIR}libft.a
MLIBX := ${MLIBXDIR}libmlx.a ${MLIBXDIR}libmlx_Linux.a

CFLAGS = -Wall -Wextra -Werror -ggdb

LFLAGS := -I${LIBFTDIR} -I${MLIBXDIR} -lXext -lX11 -lm -lz

all: ${NAME}

${NAME}:  ${OBJS} ${LIBFT} ${MLIBX}
	${CC} ${OBJS} ${LIBFT} ${MLIBX} ${MLIBX_OS} ${LFLAGS} -o ${NAME}


%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

${MLIBX}:
	cd ${MLIBXDIR} && ./configure

${LIBFT}:
	cd ${LIBFTDIR} && make bonus

clean:
	cd ${MLIBXDIR} && ./configure clean
	cd ${LIBFTDIR} && make clean
	rm -f ${OBJS}

fclean: clean
	cd ${LIBFTDIR} && make fclean
	rm -f ${NAME}

re: fclean all

.PHONY: fclean clean all re bonus
