#include "../../includes/builtins.h"
#include "../../includes/parser.h"

t_env_var *environ_to_linked_list_recursive(t_env_var *head, char** environ)
{
	char	**env_var;
	char *p;

	head = NULL;
	if (*environ != NULL)
	{
		head = malloc(sizeof(*head));
		if (head == NULL)
			exit(EXIT_FAILURE);

		// PWD=/pwd/tests
		p = ft_strchr(*environ, '=');
		head->key = malloc(sizeof(*(head->key)) * ((p - *environ) + 1));
		if (head->key == NULL)
			exit(EXIT_FAILURE);
		ft_strlcpy(head->key, *environ, (p - *environ) + 1);

		p = p + 1;
		head->value = malloc(sizeof(*(head->value)) * (ft_strlen(p) + 1));
		if (head->value == NULL)
			exit(EXIT_FAILURE);
		ft_strlcpy(head->value, p, ft_strlen(p) + 1);
		head->next = environ_to_linked_list_recursive(head->next, environ + 1);
	}
	return (head);
}

void	print_env_vars(t_command *command)
{
	t_env_var *head;

	head = *command->env_vars;
	while (head != NULL)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	printf("\n");
}