name				=	integration_tests
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
						obj/return_value.o
minishell_objects	=	../../obj/change_dir.o \
						../../obj/echo.o \
						../../obj/env.o \
						../../obj/executor_utils.o \
						../../obj/executor.o \
						../../obj/exit.o \
						../../obj/expander_data.o \
						../../obj/expander_utils.o \
						../../obj/expander.o \
						../../obj/export.o \
						../../obj/free_breezy.o \
						../../obj/parser_utils.o \
						../../obj/parser.o \
						../../obj/processes.o \
						../../obj/pwd.o \
						../../obj/tokenizer_utils.o \
						../../obj/tokenizer.o \
						../../obj/unset.o
libft	=				../../src/libft

all : $(name)

$(name) : $(test_objects)
	$(CC) -o $(name) $(test_objects) -lcriterion $(minishell_objects) -lreadline -L$(libft) -l:libft.a

obj/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $<

clean : 
	rm -rf obj

fclean : clean
	rm -f $(name)

re : fclean all

.PHONY: all clean fclean re libft libmlx