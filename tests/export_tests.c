#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/libft/libft.h"

extern char **environ;

typedef struct s_env_var
{
	char *env_var;
	struct s_env_var *next;
}	t_env_var;

void	free_env_vars(t_env_var *head)
{
	if (head->next)
		free_env_vars(head->next);
	free(head->env_var);
	free(head);
}

int count_env_vars(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	return (i);
}

t_env_var	*add_env_var(char *content)
{
	t_env_var	*node;

	node = malloc(sizeof(*node));
	if (node == NULL)
		exit(EXIT_FAILURE);
	node->env_var = ft_strdup(content);
	node->next = NULL;
	if (node->env_var == NULL)
		exit(EXIT_FAILURE);
	return (node);
}

t_env_var	*environ_to_linked_list(char** environ)
{
	int			i;
	int			number_of_nodes;
	t_env_var	*head;
	t_env_var	*node;

	i = 0;
	head = NULL;
	number_of_nodes = count_env_vars(environ);
	while (i < number_of_nodes)
	{
		node = add_env_var(environ[i]);
		if (head == NULL)
			head = node;
		else
		{
			node->next = head;
			head = node;
		}
		i++;
	}
	return (head);
}

t_env_var *environ_to_linked_list_recursive(t_env_var *head, char** environ)
{
	if (*environ != NULL)
	{
		head = malloc(sizeof(*head));
		if (head == NULL)
			exit(EXIT_FAILURE);
		head->env_var = ft_strdup(*environ);
		if (head->env_var == NULL)
			exit(EXIT_FAILURE);
		head->next = NULL;
		head->next = environ_to_linked_list_recursive(head->next, environ + 1);
	}
	return (head);
}

void	print_env_vars(t_env_var *head)
{
	while (head != NULL)
	{
		printf("|%s|\n", head->env_var);
		head = head->next;
	}
	printf("\n");
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


int main(void)
{
	// int n = get_number_of_nodes(environ);
	// printf("n = %i\n", n);

	t_env_var *head;
	head = NULL;
	head = environ_to_linked_list(environ);
	print_env_vars(head);

	// t_env_var *new = add_env_var("jon=aegon");
	// new->next = head;
	// head = new;
	// print_env_vars(head);

	// t_env_var *head;
	// head = NULL;
	// head = environ_to_linked_list_recursive(head, environ);
	// print_env_vars(head);

	free_env_vars(head);
	return (0);
}
