NAME		=	fdf
ARCHIVE		=	fdf_lib.a

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3

AR			=	ar
ARFLAGS		=	-rcs

MLXFLAGS	=	-Lmlx -lmlx -lX11 -lXext -lm
MLXDIR		=	mlx

SRCS		=	fdf_parser.c fdf_utils.c fdf_map_validator.c fdf_draw.c \
				fdf_draw_utils.c fdf_gradient.c fdf_rotate.c fdf_keyboard.c

OBJS		=	$(SRCS:%.c=%.o)

RM			=	rm -rf

all : mlx $(ARCHIVE) $(NAME)

mlx:
	make -C ./$(MLXDIR)

$(ARCHIVE) : $(OBJS)
	make -C ./includes/gnl
	make -C ./includes/libft

	$(AR) x ./includes/gnl/gnl.a
	$(AR) x ./includes/libft/libft.a

	$(AR) $(ARFLAGS) $(ARCHIVE) $(OBJS) get_next_line.o get_next_line_utils.o \
	ft_isdigit.o ft_strlcpy.o ft_strcmp.o ft_atoi.o ft_split.o ft_calloc.o

	rm -f get_next_line.o get_next_line_utils.o \
	ft_isdigit.o ft_strlcpy.o ft_strcmp.o ft_atoi.o ft_split.o ft_calloc.o

	make -C ./includes/gnl clean
	make -C ./includes/libft clean

$(NAME):
	$(CC) $(CFLAGS) fdf_main.c $(ARCHIVE) $(MLXFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
	make -C ./$(MLXDIR) clean

fclean : clean
	rm -rf ./includes/gnl/gnl.a
	rm -rf ./includes/libft/libft.a
	$(RM) $(NAME) $(ARCHIVE)

re: fclean all

.PHONY: all mlx clean fclean re