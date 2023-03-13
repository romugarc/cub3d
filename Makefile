NAME	= cub3D

SRCS	=	main.c parsing.c cub_utils.c

HEADER_FILES = cub3d.h

OBJS	=	${SRCS:.c=.o}

CC		=	gcc
RM		=	rm -f

CFLAGS	=	-Wall -Wextra #-g #-Werror #-fsanitize=address

LFLAGS	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all:		${NAME}

%.o : %.c 	${HEADER_FILES}
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@$(MAKE) -C ./mlx_linux
			@$(MAKE) -C ./libft
			@${CC} ${CFLAGS} ${OBJS} ${LFLAGS} ./libft/libft.a -o cub3D

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} cub3D
			${MAKE} -C ./mlx_linux clean
			${MAKE} -C ./libft fclean

re:			fclean all

.PHONY:		all clean fclean re cub3D
