NAME		:=	minishell
VPATH		:=	src:\
				src/parser:\
				src/tokenizer:\
				src/expander: \
				src/builtins: \
				src/executor: \
				src/heredoc: \
				src/signals:
HEADERS		:=	includes/parser.h \
				includes/tokenizer.h \
				includes/expander.h \
				includes/structs.h \
				includes/builtins.h \
				includes/executor.h \
				includes/minishell.h \
				includes/heredoc.h \
				includes/signals.h
MAIN		:=	obj/main.o
OBJECTS		:=	obj/change_dir.o \
				obj/echo.o \
				obj/env.o \
				obj/executor_utils.o \
				obj/executor_utils_cont.o \
				obj/executor.o \
				obj/exit.o \
				obj/expander_utils.o \
				obj/expand_envp.o \
				obj/expand_args.o \
				obj/expander.o \
				obj/export.o \
				obj/free_breezy.o \
				obj/parser_utils.o \
				obj/parser.o \
				obj/processes.o \
				obj/pwd.o \
				obj/tokenizer_utils.o \
				obj/tokenizer.o \
				obj/unset.o \
				obj/signals.o \
				obj/minishell_utils.o \
				obj/heredoc.o
TEST_FILES	:=	tests/parser_tests.c \
				tests/cd_tests.c \
				tests/echo_tests.c \
				tests/expander_tests.c \
				tests/export_tests.c \
				tests/tokenizer_tests.c \
				tests/unset_tests.c
CFLAGS		?=	-Wall -Wextra -Werror
LDFLAGS		?=	-lreadline
LIBFT		:=	src/libft
ITESTS		:=	tests/integration_tests

all : libft $(NAME)

libft:
	make -C $(LIBFT)

$(NAME) :$(MAIN) $(OBJECTS)
	$(CC) -o $(NAME) $(MAIN) $(OBJECTS) -L$(LIBFT) -l:libft.a $(LDFLAGS)

itests: all
	make -C $(ITESTS)

tests : all
	$(CC) -o run_tests $(TEST_FILES) -lcriterion $(OBJECTS) -L$(LIBFT) -l:libft.a $(LDFLAGS) 

obj/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	make clean -C $(LIBFT)
	make clean -C $(ITESTS)
	rm -rf obj

fclean : clean
	make fclean -C $(LIBFT)
	make fclean -C $(ITESTS)
	rm -f $(NAME)
	rm -f run_tests

re : fclean all

.PHONY: all clean fclean re libft libmlx