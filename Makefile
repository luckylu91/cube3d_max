CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
NAME =			Cub3D
LIBFT_DIR =		libft
LIBFT =			$(LIBFT_DIR)/libft.a
PRINTF_DIR =	ft_printf
PRINFT =		$(PRINTF_DIR)/libftprintf.a
# LFLAGS =		-L. -lmlx -framework OpenGL -framework AppKit -lm -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf
LFLAGS =		-L. -lmlx -lXext -lX11 -lm -L$(PRINTF_DIR) -lftprintf -L$(LIBFT_DIR) -lft # linux
IFLAGS =		-I. -I$(LIBFT_DIR) -I$(PRINTF_DIR) -Iparsing
DBFLAGS =		-fsanitize=address -g3
#DBFLAGS =		-g -O3
SRCS =			utils.c
SRCS +=			ray_march.c
SRCS +=			render.c
SRCS +=			hooks.c
SRCS +=			collision.c
SRCS +=			main_loop.c
SRCS +=			minimap.c
SRCS +=			ia.c
SRCS +=			list_utils.c
SRCS +=			parsing/file_to_list.c
SRCS +=			parsing/generic_errors.c
SRCS +=			parsing/get_next_line.c
SRCS +=			parsing/get_next_line_utils.c
SRCS +=			parsing/image_create.c
SRCS +=			parsing/image_errors.c
SRCS +=			parsing/map_check.c
SRCS +=			parsing/map_create.c
SRCS +=			parsing/map_errors.c
SRCS +=			parsing/map_objects_init.c
SRCS +=			parsing/pack_init.c
SRCS +=			parsing/free_pack.c
SRCS +=			parsing/params_parse.c
SRCS +=			parsing/parse.c
SRCS +=			parsing/split_utils.c
SRCS +=			parsing/textual_check.c
OBJS = $(SRCS:.c=.o)
HEADERS = cub3d.h
HEADERS += parsing/parse.h
HEADERS += mlx.h
#HEADERS += linux.h #linux
EXECS =			$(patsubst _%.c,%,$(wildcard _*.c))
EXECSDB =		$(patsubst %,%_db,$(EXECS))

all:	$(OBJS) $(HEADERS)
	$(CC) -o render _render.c $(OBJS) $(IFLAGS) $(LFLAGS)

%:			_%.c $(OBJS)
	$(CC) -o $@ $< $(OBJS) $(IFLAGS) $(LFLAGS) 

%_db:		_%.c $(OBJS)
	$(CC) -o $@ $< $(DBFLAGS) $(OBJS) $(IFLAGS) $(LFLAGS)

%.o:		%.c $(HEADERS)
	$(CC) -c -o $@ $< $(IFLAGS)

libft:
	make -C $(LIBFT_DIR) bonus
	make -C $(LIBFT_DIR) clean

printf:
	make -C $(PRINTF_DIR)
	make -C $(PRINTF_DIR) clean

clean:
	rm -f $(OBJS)

fclean:	clean
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	rm -f $(EXECS)
	rm -f $(EXECSDB)

re:	fclean all

.PHONY:	clean fclean libft printf re
