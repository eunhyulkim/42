#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <fcntl.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void)
{
    int server_socket;
    int str_len;
    char message[30];
    struct sockaddr_in server_address;

    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }
    memset(message, 0, sizeof(message));
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(3600);

    if (connect(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        printf("connect error\n");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
	write(server_socket, "TEST", 4);
    if (read(server_socket, message, sizeof(message)) == -1) {
        printf("read error\n");
    } else {
        printf("success, response message is %s", message);
    }
    close(server_socket);

    return (0);
}

