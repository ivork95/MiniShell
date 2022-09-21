test_objects		=	simple_command.o

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

integration_tests : $(test_objects)
	gcc -o integration_tests $(test_objects) -lcriterion $(minishell_objects) -lreadline -L../../src/libft -l:libft.a

simple_command.o: simple_command.c
	gcc -c simple_command.c

clean : 
	rm integration_tests $(test_objects)