#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include "../includes/parser.h"
#include "../includes/tokenizer.h"

Test(test_tokenizer, cmd_line)
{
	char	*s = "\'helloo\'   world|test  ||   this \"string   \"        \"forme\"<outfile>>       \"quotes > not | closed  ";
	t_token	*list;

	list = tokenizer(s);
    char *output[13] = {"\'helloo\'", "world","|","test",  "|", "|"  ,"this", "\"string   \"",   "\"forme\"", "<", "outfile", ">>", "\"quotes > not | closed  "};

    int i = 0;
    while (list)
    {
        char *test_str = malloc(sizeof(char *) * list->len + 1);
        ft_strlcpy(test_str, list->str, list->len + 1);
        cr_assert(eq(str, output[i], test_str));
        list = list->next;
        free(test_str);
        i++;
    }
}
