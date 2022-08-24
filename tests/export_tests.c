#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/libft/libft.h"

extern char **environ;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

void	print_env_vars(t_env_var *head)
{
	while (head != NULL)
	{
		printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	printf("\n");
}

void	free_env_vars(t_env_var *head)
{
	if (head->next)
		free_env_vars(head->next);
	free(head->key);
	free(head->value);
	free(head);
}

t_env_var	*add_env_var(char *key, char *value)
{
	t_env_var	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		exit(EXIT_FAILURE);
	node->key = ft_strdup(key);
	if (node->key == NULL)
		exit(EXIT_FAILURE);
	node->value = ft_strdup(value);
	if (node->value == NULL)
		exit(EXIT_FAILURE);
	node->next = NULL;
	return (node);
}

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

		// env_var = ft_split(*environ, '=');
		// if (env_var == NULL)
		// 	exit(EXIT_FAILURE);
		// head->key = env_var[0];
		// head->value = env_var[1];
		// free(env_var);
		head->next = environ_to_linked_list_recursive(head->next, environ + 1);
	}
	return (head);
}

int main(void)
{
	// int n = get_number_of_nodes(environ);
	// printf("n = %i\n", n);

	// t_env_var *head;
	// head = NULL;
	// head = environ_to_linked_list(environ);
	// print_env_vars(head);

	// t_env_var *new = add_env_var("jon=aegon");
	// new->next = head;
	// head = new;
	// print_env_vars(head);

	t_env_var *head;
	head = NULL;
	head = environ_to_linked_list_recursive(head, environ);
	print_env_vars(head);

	free_env_vars(head);
	return (0);
}

// zet env om in linked list
// hoeveel nodes heb ik nodig
// 

// Test(export, echo_simple)
// {
//     /*
//     input is export jon=aegon
//     expected output is an additional environmental variable jon=aegon

//     je kan checken of er een key value pair bij is gekomen
//     tel het aantal key value pairs
//     na het runnen van de function moet er een bij zijn gekomen
//     hoe pak je in c env values op? getenv()
//     hoe voeg je environment variable to met c?

//     pak hele environment
//     malloc en kopieer
//     voeg nieuwe entry toe
//     vervang oude environment door nieuwe, hoe? verplaats pointer?
//     */

//     // char *env_var = getenv("HOME"); // /root
//     // printf("env_var = |%s|\n", env_var);
//     // cr_assert(eq(str, "/root", env_var));

//     // char *env_var = getenv("JON"); // null
//     // printf("env_var = |%s|\n", env_var);
//     // cr_assert(eq(str, "/root", env_var));

//     // char *env_var = getenv("jon"); // /root
//     // cr_assert(eq(str, "aegon", env_var));

//     int i = 0;
//     while (environ[i])
//     {
//         printf("|%s|\n", environ[i]);
//         i++;
//     }
// }
