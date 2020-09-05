#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <fcntl.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int error_handling(char *message, int server_socket) {
    printf("%s\n", message);
    close(server_socket);
    return (EXIT_FAILURE);
}

unsigned int ft_htonl(unsigned int little)
{
    unsigned char bytes[4];
    unsigned int ret;
    unsigned char is_little;

    ret = 1;
    is_little = (ret & 0xff) << 24 != 0;
    if (is_little)
        return (little);
    bytes[0] = (unsigned char)((little >> 0) & 0xff);
    bytes[1] = (unsigned char)((little >> 8) & 0xff);
    bytes[2] = (unsigned char)((little >> 16) & 0xff);
    bytes[3] = (unsigned char)((little >> 24) & 0xff);
    ret = ((unsigned int)bytes[0] << 24 | (unsigned int)bytes[1] << 16
    | (unsigned int)bytes[2] << 8 | (unsigned int)bytes[3] << 0);
    return (ret);
}

int main(void)
{
    int server_socket;
    int client_socket;
    socklen_t client_address_size;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

   if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        return (error_handling("socket error", server_socket));
     
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.200.131");
    // server_address.sin_addr.s_addr = ft_htonl(INADDR_ANY);
    server_address.sin_port = htons(4000);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
        return (error_handling("bind error", server_socket));
    if (listen(server_socket, 5) == -1)
        return (error_handling("listen error", server_socket));

    memset(&client_address, 0, sizeof(client_address));
    client_address_size = sizeof(client_address);

    client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
    if (client_socket == -1)
        return (error_handling("accept error", server_socket));
    char msg[] = "HTTP/1.1 200 OK\r\nContent-Length: 25\r\n\r\n<p>welcome, 42 webserver!</p>";
    write(client_socket, msg, sizeof(msg));

    close(server_socket);
    close(client_socket);

    return (0);
}

