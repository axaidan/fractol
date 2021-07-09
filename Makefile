NAME		=	fractol	

CC			=	gcc

SRCS		=	main.c \
				initializations.c \
				system.c \
				errors.c \
				fractol.c \
				utils_mlx.c \
				hooks.c \
				display.c \
				render.c \
				move.c \
				bmp.c

SRCS_DIR	=	srcs

OBJS		=	${addprefix ${SRCS_DIR}/,${SRCS:.c=.o}}

LIBFT_DIR	=	libft

MLX_DIR		=	mlx

INCLUDE_DIR	=	includes

HEADERS		=	-I ${INCLUDE_DIR} -I ${LIBFT_DIR} -I ${MLX_DIR} 

#CFLAGS		=	-Wall -Wextra -Werror -O3 -flto
CFLAGS		=	-Wall -Wextra -Werror

LIB_LINK	=	-L ${LIBFT_DIR} -L ${MLX_DIR}

ALL_LIBS	=	-lm -lft -lmlx -lXext -lX11

%.o		:	%.c ${INCLUDE_DIR}/fractol.h ${INCLUDE_DIR}/errors.h ${INCLUDE_DIR}/defines.h ${INCLUDE_DIR}/structures.h
	${CC} ${CFLAGS} ${HEADERS} -c $< -o ${<:.c=.o}

all		:	${NAME}

$(NAME)	:	${OBJS}
	make -C ${LIBFT_DIR}
	make -C ${MLX_DIR}
	${CC} ${CFLAGS} ${LIB_LINK} ${OBJS} -o ${NAME} ${ALL_LIBS}

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

