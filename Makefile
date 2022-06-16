VPATH :=	src:\
			src/parser:
NAME := minishell
HEADERS := includes/parser.h
OBJECTS :=	obj/main.o \
			obj/parser.o

CFLAGS ?= -Wall -Wextra # -Werror
LDFLAGS ?= -lreadline
LIBFT := src/libft

all : libft $(NAME)

libft:
	make -C $(LIBFT)

$(NAME) : $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LIBFT)/libft.a $(LDFLAGS)

obj/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	make clean -C $(LIBFT)
	rm -f $(OBJECTS)

fclean : clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re libft libmlx