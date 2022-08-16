NAME		:=	minishell

VPATH		:=	src:\
				src/parser:\
				src/tokenizer:\
				src/expander:
HEADERS		:=	includes/parser.h \
				includes/tokenizer.h
MAIN		:=	obj/minishell.o
OBJECTS		:=	obj/parser.o \
				obj/parser_utils.o \
				obj/free_breezy.o \
				obj/tokenizer.o \
				obj/tokenizer_utils.o \
				obj/expander.o
TEST_FILES	:=	tests/parser_tests.c \
				tests/tokenizer_tests.c \
				tests/expander_tests.c

CFLAGS		?=	-Wall -Wextra # -Werror
LDFLAGS		?=	-lreadline

LIBFT		:=	src/libft

all : libft $(NAME)

libft:
	make -C $(LIBFT)

$(NAME) : $(OBJECTS) $(MAIN)
	$(CC) -o $(NAME) $(MAIN) $(OBJECTS) $(LIBFT)/libft.a $(LDFLAGS)

tests : all
	$(CC) -o run_tests $(TEST_FILES) $(OBJECTS) $(LIBFT)/libft.a $(LDFLAGS) -lcriterion

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