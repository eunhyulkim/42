#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
** Useful Macros
*/
# define SIGN(x)		(x > 0) ? "POS" : ((x == 0) ? "ZERO" : "NEG")
# define TEST_STRLEN(x)		printf("`%s` -> %d == %d\n", x, ft_strlen(x), \
							(int)strlen(x))
# define TEST_STRCMP(a, b)	printf("`%s`:`%s` -> %s == %s\n", a, b, \
							SIGN(ft_strcmp(a, b)), SIGN(strcmp(a, b)))
/*
** Function Prototype
*/
int			ft_strlen(const char *src);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, const char *src);
ssize_t		ft_write(int fd, const void *buf, size_t size);
ssize_t		ft_read(int fd, void *buf, size_t size);
char		*ft_strdup(const char *s1);

void	test_strdup(char *s1, char *s2)
{
	char	*src = 0;
	char	*ret = 0;

	src = strdup(s1);
	ret = ft_strdup(s2);
	printf("`%s`->`%s`", src, ret);
	if (src == ret)
		printf(" -> SRC & RET IS SAME REF\n");
	else
		printf(" -> SUCCESS REF\n");
	free(src);
	free(ret);
}

void	test_strcpy(char *d, char *src)
{
	char	dest[100];

	memset(dest, 0, 100);
	strcpy(dest, d);
	if (dest != ft_strcpy(dest, src))
		printf("[INVALID RETURN]");
	printf("`%s`->`%s`", src, dest);
	if (src == dest)
		printf(" -> SRC & RET IS SAME REF\n");
	else
		printf(" -> SUCCESS REF\n");
}

void	test_write(int fd, char *src, int size)
{
	int	src_ret = 0;
	int ft_ret = 0;

	write(1, "`", 1);
	ft_ret = ft_write(fd, src, size);
	write(1, "`:`", 3);
	src_ret = write(fd, src, size);
	printf("` -> %d:%d\n", src_ret, ft_ret);
}

void	test_read(int fd, int size)
{
	int		sfd;
	int		mfd;
	int		sret;
	int		mret;
	char	sbuff[100];
	char	mbuff[100];

	sfd = (fd == 42) ? open("ft_write.s", O_RDONLY) : fd;
	memset(sbuff, 0, 100);
	sret = read(sfd, sbuff, size);
	printf("(%d) -> %d", printf("%s", sbuff), sret);
	close(sfd);
	printf(" : ");
	mfd = (fd == 42) ? open("ft_write.s", O_RDONLY) : fd;
	memset(mbuff, 0, 100);
	mret = read(mfd, mbuff, size);
	printf("(%d) -> %d\n", printf("%s", mbuff), mret);
	close(mfd);
}

int main(void)
{
	printf(">---------FT_STRLEN_TEST---------<\n\n");
	TEST_STRLEN("");
	TEST_STRLEN("0123456789");
	TEST_STRLEN("HELLO, WORLD!");

	printf("\n>---------FT_STRCMP_TEST---------<\n\n");
	TEST_STRCMP("", "");
	TEST_STRCMP("", "TEST");
	TEST_STRCMP("TEST", "");
	TEST_STRCMP("TEST", "TES");
	TEST_STRCMP("TESA", "TEST");

	printf("\n>---------FT_STRDUP_TEST---------<\n\n");
	test_strdup("", "");
	test_strdup("12345", "12345");
	test_strdup("EMPTY", "EMPTY");

	printf("\n>---------FT_STRCPY_TEST---------<\n\n");
	test_strcpy("", "");
	test_strcpy("   ", "");
	test_strcpy("12345", "123");
	test_strcpy("EMPTY", "EM");

	printf("\n>---------FT_WRITE_TEST---------<\n\n");
	test_write(1, "TEST", 4);
	test_write(1, "TEST", 2);
	test_write(1, "TEST", 6);
	test_write(1, "TEST", 0);
	test_write(150, "TEST", 4);
	test_write(-1, "TEST", 4);

	printf("\n>---------FT_READ_TEST---------<\n\n");
	test_read(42, -1);
	test_read(-1, 3);
	test_read(42, 0);
	test_read(42, 1);
	test_read(42, 3);

	return (0);
}
