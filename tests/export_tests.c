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

int get_number_of_nodes(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	return (i);
}

// head moet NULL zijn of bestaan
t_env_var *malloc_linked_list(char** environ)
{
	int			i;
	int			number_of_nodes;
	t_env_var	*head;
	t_env_var	*new;

	i = 0;
	head = NULL;
	number_of_nodes = get_number_of_nodes(environ);
	while (i < number_of_nodes)
	{
		new = malloc(sizeof(*new));
		if (new == NULL)
			exit(EXIT_FAILURE);
		if (head == NULL)
			head = new;
		else
		{
			new->next = head;
			head = new;
		}
		i++;
	}
	return (head);
}

void copy_env(t_env_var *head, char **environ)
{
	int i;

	i = 0;
	while (head != NULL)
	{
		head->env_var = ft_strdup(environ[i]);
		head = head->next;
		i++;
	}
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
	head = malloc_linked_list(environ);
	copy_env(head, environ);

	int i = 0;
	while (head != NULL)
	{
		printf("str = |%s|\n", head->env_var);
		head = head->next;
		i++;
	}
	printf("i = %i\n", i);
	return (0);
}
