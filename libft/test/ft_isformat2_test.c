#include <stdio.h>
#include "libft.h"

void test(char *s1, char *mask, char *expect)
{
	char	*res;

	res = ft_isformat2(s1, mask) ? "TRUE" : "FALSE";
	printf("%-16s%-16s%-16s%-16s\n", s1, mask, res, expect);
}

int main(void)
{
	printf("%-16s%-16s%-16s%-16s\n", "STR", "MASK", "RES", "EXPECT");
	test("abc.txt", "*", "TRUE");
	test("abc.txt", "a*", "TRUE");
	test("abc.txt", "*t", "TRUE");
	test("abc.txt", "abc*", "TRUE");
	test("abc.txt", "*txt", "TRUE");
	test("abc.txt", "*bc*", "TRUE");
	test("abc.txt", "*abc*", "TRUE");
	test("abc.txt", "*txt*", "TRUE");
	test("abc.txt", "ab*.t*t", "TRUE");
	test("abc.txt", "ab**.t*t", "TRUE");
	test("abc.txt", "abc**.tx*t", "TRUE");
	test("abc.txt", "****", "TRUE");
	test("abc.txt", "****t", "TRUE");
	test("abc.abc", "*bc", "TRUE");

	test("abc.txt", "bc.tx", "FALSE");
	test("abc.txt", "abc.tx", "FALSE");
	test("abc.txt", "bc.txt", "FALSE");
	test("abc.txt", "b*.txt", "FALSE");
	test("abc.txt", "ab*.yt", "FALSE");
	test("abc.txt", "abc*c.txt", "FALSE");
	test("abc.abc", "*bd", "FALSE");
	return (0);
}
