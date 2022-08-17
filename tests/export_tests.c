#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <stdlib.h>

Test(export, echo_simple)
{
    /*
    input is export jon=aegon
    expected output is an additional environmental variable jon=aegon

    je kan checken of er een key value pair bij is gekomen
    tel het aantal key value pairs
    na het runnen van de function moet er een bij zijn gekomen
    hoe pak je in c env values op? getenv()
    hoe voeg je environment variable to met c?

    pak hele environment
    malloc en kopieer
    voeg nieuwe entry toe
    vervang oude environment door nieuwe, hoe? verplaats pointer?
    */

    // char *env_var = getenv("HOME"); // /root
    // printf("env_var = |%s|\n", env_var);
    // cr_assert(eq(str, "/root", env_var));

    // char *env_var = getenv("JON"); // null
    // printf("env_var = |%s|\n", env_var);
    // cr_assert(eq(str, "/root", env_var));

    char *env_var = getenv("jon"); // /root
    cr_assert(eq(str, "aegon", env_var));
}
