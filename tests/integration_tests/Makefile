name				=	../../integration_tests
header				=	minicore.h
test_objects		=	obj/simple_command.o \
						obj/arguments.o \
						obj/echo.o \
						obj/exit.o \
						obj/double_quotes.o \
						obj/single_quotes.o \
						obj/relative_path.o \
						obj/environment_path.o \
						obj/env.o \
						obj/export.o \
						obj/unset.o \
						obj/cd.o \
						obj/pwd.o \
						obj/return_value.o \
						obj/pipes.o \
						obj/minicore.o \
						obj/test_expander.o
minishell_objects	=	../../obj/change_dir.o \
						../../obj/echo.o \
						../../obj/env.o \
						../../obj/executor_utils.o \
						../../obj/executor_utils_cont.o \
						../../obj/executor.o \
						../../obj/exit.o \
						../../obj/expander_utils.o \
						../../obj/expand_envp.o \
						../../obj/expand_args.o \
						../../obj/expander.o \
						../../obj/export.o \
						../../obj/free_breezy.o \
						../../obj/parser_utils.o \
						../../obj/parser.o \
						../../obj/processes.o \
						../../obj/pwd.o \
						../../obj/tokenizer_utils.o \
						../../obj/tokenizer.o \
						../../obj/unset.o \
						../../obj/signals.o \
						../../obj/minishell_utils.o \
						../../obj/heredoc.o
libft	=				../../src/libft
LDFLAGS	?=				-lreadline

all : $(name)

$(name) : $(test_objects)
	$(CC) -o $(name) $(test_objects) -lcriterion $(minishell_objects) -L$(libft) -l:libft.a $(LDFLAGS)

obj/%.o : %.c $(header)
	@mkdir -p $(dir $@)
	$(CC) -g -fsanitize=address -c -o $@ $<

clean : 
	rm -rf obj

fclean : clean
	rm -f $(name)

re : fclean all

.PHONY: all clean fclean re libft libmlx