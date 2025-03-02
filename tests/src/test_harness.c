#include <criterion/criterion.h>
#include "pseudo.h"

Test(math_ops, test_add)
{
	int	result;

	result = simple_add(2, 3);
	cr_assert_eq(result, 5, "Expected 2 + 3 to equal 5");
}