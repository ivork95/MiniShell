#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>

void redirect_all_stdout(void)
{
		cr_redirect_stdout();
		cr_redirect_stderr();
}

int error(void)
{
		write(2, "apple", 5);
		exit(0);
}

Test(errors, exit_code, .init=redirect_all_stdout, .exit_code = 0)
{
		error();
		cr_assert_stderr_eq_str("error", "");
}