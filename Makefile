NAME		:=	minishell
VPATH		:=	src:\
				src/parser:\
				src/tokenizer:\
				src/expander: \
				src/builtins:
HEADERS		:=	includes/parser.h \
				includes/tokenizer.h \
				includes/expander.h \
				includes/structs.h \
				includes/builtins.h
MAIN		:=	obj/main.o
OBJECTS		:=	obj/parser.o \
				obj/parser_utils.o \
				obj/free_breezy.o \
				obj/tokenizer.o \
				obj/tokenizer_utils.o \
				obj/expander.o \
				obj/expander_utils.o \
				obj/expander_data.o \
				obj/echo.o \
				obj/pwd.o \
				obj/env.o \
				obj/change_dir.o \
				obj/export.o \
				obj/unset.o \
				obj/exit.o
TEST_FILES	:=	tests/parser_tests.c \
				tests/cd_tests.c \
				tests/echo_tests.c \
				tests/expander_tests.c \
				tests/export_tests.c \
				tests/tokenizer_tests.c \
				tests/unset_tests.c
CFLAGS		?=	-Wall -Wextra -g # -Werror
LDFLAGS		?=	-lreadline
LIBFT		:=	src/libft

all : libft $(NAME)

libft:
	make -C $(LIBFT)

$(NAME) :$(MAIN) $(OBJECTS)
	$(CC) -o $(NAME) $(MAIN) $(OBJECTS) -L$(LIBFT) -l:libft.a $(LDFLAGS)

tests : all
	$(CC) -o run_tests $(TEST_FILES) -lcriterion $(OBJECTS) -L$(LIBFT) -l:libft.a $(LDFLAGS) 

obj/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	make clean -C $(LIBFT)
	rm -rf obj

fclean : clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm -f run_tests

re : fclean all

.PHONY: all clean fclean re libft libmlx