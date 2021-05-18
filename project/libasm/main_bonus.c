#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/*
** List structure
*/
typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

/*
** Useful Macros
*/


/*
** Function Prototype
*/
int			ft_strlen(const char *src);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, const char *src);
ssize_t		ft_write(int fd, const void *buf, size_t size);
ssize_t		ft_read(int fd, void *buf, size_t size);
char		*ft_strdup(const char *s1);

/*
** Bonus Function Prototypes
*/
int		ft_atoi_base(char *str, char *base);
void	ft_list_push_front(t_list **begin, void *data);
int		ft_list_size(t_list *begin_list);
void	ft_list_sort(t_list **begin_list, int (*cmp)());
int		ft_list_remove_if(t_list **begin_list, void *data_ref, \
		int (*cmp)(), void (*free_fct)(void *));


void	test_atoi_base(char *src, char *base, int ans)
{
	int		ret;

	ret = ft_atoi_base(src, base);
	printf("%d : %d ", ret, ans);
	if (ret == ans)
		printf("-> SUCCESS\n");
	else
		printf("-> FAIL\n");
}

void	test_push_front(char *src, char *ans)
{
	t_list	*begin;
	t_list	*element;
	t_list	*temp;
	char	str[2];
	int		idx;

	begin = NULL;
	idx = 0;
	str[1] = '\0';
	while (src[idx])
	{
		str[0] = src[idx++];
		ft_list_push_front(&begin, ft_strdup(str));
	}
	element = begin;
	while (begin)
	{
		printf("%s", begin->data);
		begin = begin->next;
	}
	printf(" : %s\n", ans);
	while (element)
	{
		temp = element->next;
		free(element->data);
		free(element);
		element = temp;
	}
}

void	test_list_size(char *src, int ans)
{
	t_list	*begin;
	t_list	*element;
	t_list	*temp;
	char	str[2];
	int		idx;

	begin = NULL;
	idx = 0;
	str[1] = '\0';
	while (src[idx])
	{
		str[0] = src[idx++];
		ft_list_push_front(&begin, ft_strdup(str));
	}
	element = begin;
	idx = ft_list_size(begin);
	while (begin)
	{
		printf("%s", begin->data);
		begin = begin->next;
	}
	printf(" %d : %d\n", idx, ans);
	while (element)
	{
		temp = element->next;
		free(element->data);
		free(element);
		element = temp;
	}
}

void	test_list_sort(char *s1, char *s2, char *s3, char *s4)
{
	t_list	*begin;
	t_list	*element;
	t_list	*temp;

	begin = NULL;
	ft_list_push_front(&begin, s1);
	ft_list_push_front(&begin, s2);
	ft_list_push_front(&begin, s3);
	ft_list_push_front(&begin, s4);
	ft_list_sort(&begin, ft_strcmp);

	element = begin;
	while (begin)
	{
		printf("%s ", begin->data);
		begin = begin->next;
	}
	printf("\n");
	while (element)
	{
		temp = element->next;
		free(element);
		element = temp;
	}
}

void	test_list_remove(char *s1, char *s2, char *s3, char *s4)
{
	t_list	*begin;
	t_list	*element;
	t_list	*temp;

	begin = NULL;
	ft_list_push_front(&begin, strdup(s1));
	ft_list_push_front(&begin, strdup(s2));
	ft_list_push_front(&begin, strdup(s3));
	ft_list_push_front(&begin, strdup(s4));
	ft_list_remove_if(&begin, "A", ft_strcmp, free);
	element = begin;
	printf("%s %s %s %s -> ", s4, s3, s2, s1);
	while (begin)
	{
		printf("%s ", begin->data);
		begin = begin->next;
	}
	printf("\n");
	while (element)
	{
		free(element->data);
		temp = element->next;
		free(element);
		element = temp;
	}
}

int main(void)
{
	printf(">---------FT_ATOI_BASE_TEST---------<\n\n");
	test_atoi_base("19", "0123456789", 19);
	test_atoi_base("ABC", "0123456789ABCDEF", 2748);
	test_atoi_base("   ABC", "0123456789ABCDEF", 2748);
	test_atoi_base("+++---ABCGA", "0123456789ABCDEF", -2748);
	test_atoi_base("+++----ABCGA", "0123456789ABCDEF", 2748);
	test_atoi_base("ABC", "0123456789ABCDEFGHIJ", 4232);
	test_atoi_base("ABC", "BCA", 19);
	test_atoi_base("1101", "01", 13);
	test_atoi_base("ABC", "BCAB", 0);
	test_atoi_base("ABC", "BCA-", 0);
	test_atoi_base("ABC", "BCA+", 0);
	test_atoi_base("ABC", "BCA ", 0);
	test_atoi_base("1101", "1", 0);
	test_atoi_base(0, "1234", 0);
	test_atoi_base("", "1234", 0);
	test_atoi_base("1101", 0, 0);

	printf("\n>---------FT_PUSH_FRONT_TEST---------<\n\n");
	test_push_front("EDCBA", "ABCDE");

	printf("\n>---------FT_LIST_SIZE_TEST---------<\n\n");
	test_list_size("A", 1);
	test_list_size("BA", 2);
	test_list_size("CBA", 3);
	test_list_size("DCBA", 4);
	test_list_size("EDCBA", 5);

	printf("\n>---------FT_LIST_SORT_TEST---------<\n\n");
	test_list_sort("A", "B", "C", "D");
	test_list_sort("A", "D", "C", "B");
	test_list_sort("D", "B", "C", "A");

	printf("\n>---------FT_LIST_REMOVE_TEST---------<\n\n");
	test_list_remove("A", "B", "C", "D");
	test_list_remove("A", "D", "C", "B");
	test_list_remove("D", "B", "C", "A");
	test_list_remove("A", "A", "C", "A");
	test_list_remove("A", "A", "A", "A");

	return (0);
}
