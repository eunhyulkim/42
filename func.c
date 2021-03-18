// socket
// select, accept, listen, send, recv, bind
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  printf("%lu\n", strlen("HELLO"));
  return (0);
}

#include <unistd.h>
// ssize_t write(int fd, const void *buf, size_t count); 출력한 문자 수 || -1
// int close(int fd); 0 || -1

#include <stdlib.h>
// void *malloc(size_t size); || NULL
// void *calloc(size_t elem_count, size_t elem_size); || NULL
// void free(void *ptr);
// void *realloc (void * ptr , size_t new_size ); || NULL
// void exit(int status);
// int atoi(const char *nptr); || 0

#include <strings.h>
// void bzero(void *s, size_t n);

#include <string.h>
// char *strstr(const char *haystack, const char *needle); || NULL
// size_t strlen(const char *s) || SEGMENT FAULT;
// void *memset(void *s, int c, size_t n);
// char *strcpy(char *dest, const char *src);
// char *strcat(char *dest, const char *src);

#include <stdio.h>
// int sprintf(char *str, const char *format, ...);

#include <sys/socket.h>
// int socket(int domain, int type, int protocol); || -1
// int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); 0 || -1
// int listen(int sockfd, int backlog); 0 || -1
