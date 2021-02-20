CC =			clang
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

SRCS +=			hooks_end.c
SRCS +=			utils.c
SRCS +=			gen_draw_utils.c
SRCS +=			main_loop.c
SRCS +=			ia_path_memory.c
SRCS +=			hooks_start.c
SRCS +=			ia.c
SRCS +=			hooks_render_utils.c
SRCS +=			hooks_render_enemy2.c
SRCS +=			ia_path_utils.c
SRCS +=			ray_march.c
SRCS +=			generic_errors.c
SRCS +=			hooks_render_enemy1.c
SRCS +=			parsing/image_create.c
SRCS +=			parsing/image_errors.c
SRCS +=			parsing/parse.c
SRCS +=			parsing/map_check.c
SRCS +=			parsing/params_parse2.c
SRCS +=			parsing/image_load.c
SRCS +=			parsing/map_objects_init2.c
SRCS +=			parsing/pack_init1.c
SRCS +=			parsing/free_others.c
SRCS +=			parsing/map_objects_init1.c
SRCS +=			parsing/get_next_line_utils.c
SRCS +=			parsing/params_parse_funs2.c
SRCS +=			parsing/params_parse_utils1.c
SRCS +=			parsing/params_parse_utils2.c
SRCS +=			parsing/params_parse_funs1.c
SRCS +=			parsing/get_next_line.c
SRCS +=			parsing/map_errors.c
SRCS +=			parsing/pack_init2.c
SRCS +=			parsing/params_parse3.c
SRCS +=			parsing/file_to_list.c
SRCS +=			parsing/map_new1.c
SRCS +=			parsing/textual_check.c
SRCS +=			parsing/params_parse1.c
SRCS +=			parsing/params_parse_utils3.c
SRCS +=			parsing/split_utils.c
SRCS +=			parsing/image_utils.c
SRCS +=			parsing/free_pack.c
SRCS +=			parsing/map_new2.c
SRCS +=			generate_bmp.c
SRCS +=			list_utils.c
SRCS +=			render.c
SRCS +=			hooks_transitions.c
SRCS +=			file_errors.c
SRCS +=			hooks_render.c
SRCS +=			collision1.c
SRCS +=			minimap.c
SRCS +=			hooks_render_movements.c
SRCS +=			collision2.c


OBJS = $(SRCS:.c=.o)
HEADERS = cub3d.h
HEADERS += parsing/parse.h
HEADERS += parsing/params_parse_funs.h
HEADERS += parsing/params_parse_utils.h
HEADERS += mlx.h
# HEADERS += linux.h #linux
EXECS =			$(patsubst _%.c,%,$(wildcard _*.c))
EXECSDB =		$(patsubst %,%_db,$(EXECS))

all:	libft printf $(OBJS) $(HEADERS)
	$(CC) -o render _render.c $(OBJS) $(IFLAGS) $(LFLAGS)

db:		libft printf $(OBJS) $(HEADERS)
	$(CC) -o render _render.c $(DBFLAGS) $(OBJS) $(IFLAGS) $(LFLAGS)

%:			_%.c
	$(CC) -o $@ $< $(OBJS) $(IFLAGS) $(LFLAGS)

%_db:		_%.c
	$(CC) -o $@ $< $(DBFLAGS) $(OBJS) $(IFLAGS) $(LFLAGS)

%.o:		%.c $(HEADERS)
	$(CC) -c -o $@ $< $(IFLAGS)

libft:
	make -C $(LIBFT_DIR) bonus

printf:
	make -C $(PRINTF_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean:	clean
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	rm -f $(EXECS)
	rm -f $(EXECSDB)

re:	fclean all

.PHONY:	clean fclean libft printf re
