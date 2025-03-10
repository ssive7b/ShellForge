#include <criterion/criterion.h>
#include "pseudo.h"

Test(math_ops, test_add)
{
	int	result;

	result = simple_add(2, 3);
	cr_assert_eq(result, 5, "Expected 2 + 3 to equal 5");
}

// Tests to be implemented:
// 1. escaped <newline>s (unquoted \ + <newline>) are removed completely before tokenization, so cannot be used as separators. Check if handled correctly.s
// 2. a single quote (') cannot occur within single quotes (i.e. always need to close single quotes).
// 3. When enclosed inside double quotes (" "), check unique treatment for $, backquote ( ` ) and backlash ( \ ).
// 4. Inside the $( ... ) structure ensure and even number of single and double quotes.
// 5. When within double quotes, a single-quoted or double-quoted string that begins, but does not end, within the "`...`" sequence.
// 6. When within double quotes, a "`...`" sequence that begins, but does not end, within the same double-quoted string.
// 7. When within double quotes, the backslash shall retain its special meaning as an escape character (see Escape Character (Backslash)) 
//    only when followed by one of the following characters when considered special:$   `   "   \   <newline>