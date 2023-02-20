NAME	= cub3D

SRCS	=	main.c

HEADER_FILES = cub3d.h

OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -f

CFLAGS	=	-Wall -Wextra #-Werror #-fsanitize=address

LFLAGS	=	-lm -framework OpenGL -framework AppKit

all:		${NAME}

%.o : %.c 	${HEADER_FILES}
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@$(MAKE) -C ./minilibx_linux
			@${CC} ${CFLAGS} ${LFLAGS} ${OBJS} ./minilibx_linux/libmlx.a -o cub3D

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} cub3D
			${MAKE} -C ./minilibx_linux clean

re:			fclean all

.PHONY:		all clean fclean re cub3D
