NAME		=	fractol	

CC			=	gcc

SRCS		=	main.c \
				initializations.c \
				system.c \
				errors.c \
				fractol.c \
				utils_mlx.c

SRCS_DIR	=	srcs

OBJS		=	${addprefix ${SRCS_DIR}/,${SRCS:.c=.o}}

LIBFT_DIR	=	libft

MLX_DIR		=	mlx

INCLUDE_DIR	=	includes

HEADERS		=	-I ${INCLUDE_DIR} -I ${LIBFT_DIR} -I ${MLX_DIR} 

CFLAGS		=	-Wall -Wextra -Werror -O3 -flto

LIB_LINK	=	-L ${LIBFT_DIR} -L ${MLX_DIR}

ALL_LIBS	=	-lm -lft -lmlx -lXext -lX11

.c.o	:	${INCLUDE_DIR}/cub3d.h ${INCLUDE_DIR}/cub3d_errors.h
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

