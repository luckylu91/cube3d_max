CC =			gcc
CFLAGS =		-Wall -Wextra -Werror -I../libft
NAME =			libftprintf.a
SRCS =			parser.c \
				parser_opts1.c \
				parser_opts2.c \
				int_conv.c \
				int_conv_utils.c \
				char_conv.c \
				ft_printf.c \
				utils.c \
				conv_utils.c
OBJS =			$(SRCS:.c=.o)
RM =			rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $(OBJS)

%.o: %.c ft_printf.h
	$(CC) -c $(CFLAGS) $(IFLAGS) $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
