#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct    s_client {
  int                 id;
  int                 fd;
  struct sockaddr_in  addr;
  struct s_client     *next;
}                 t_client;

typedef struct    s_server {
  int                 fd;
  int                 max_fd;
  int                 auto_id;
  fd_set              readset;
  t_client            *clients;
  char                message[4200];
  struct sockaddr_in  addr;

  void (*send_all)(struct s_client *client, char *msg, int type);
  void (*connect_server)(char *);
  void (*clear_set)();
  void (*add_client)();
  void (*remove_client)(int remove_fd);
  void (*broadcast)();
  void (*start)();
  void (*stop)(int);
}                 t_server;

t_server g_serv;


void send_all(t_client* sender, char *msg, int type) {
  printf("SEND ALL FUNCTION EXECUTE WITH %d | %s | %d\n", sender->id, msg, type);
  t_client *client = g_serv.clients;
  
  if (!client)
    return ;

  if (!msg && type == 1)
    sprintf(g_serv.message, "server: client %d just arrived\n", sender->id);
  else if (!msg && type == 2)
    sprintf(g_serv.message, "server: client %d just left\n", sender->id);
  else if (msg)
    sprintf(g_serv.message, "client %d: %s\n", sender->id, msg);

  while (client) {
    if (client->id != sender->id)
      send(client->fd, g_serv.message, strlen(g_serv.message), 0);
    client = client->next;
  }
}

void stop_server(int status) {
  char *argument_error = "Wrong number of arguments\n";
  char *fatal_error = "Fatal error\n";
  t_client *client;

  if (status == 1) {
    write(2, argument_error, strlen(argument_error));
  } else if (status > 1) {
    write(2, fatal_error, strlen(fatal_error));
  }

  if (status != 1)
    close(g_serv.fd);
  if (status > 2) {
    while (g_serv.clients) {
      client = g_serv.clients;
      g_serv.clients = client->next;
      close(client->fd);
      free(client);
    }
  }

  exit(status == 0 ? 0 : 1);
};

void connect_server(char *port_string) {
  int port;
	
  if ((g_serv.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    g_serv.stop(1);
  printf("CONNECT: %d\n", g_serv.fd);
  if ((port = atoi(port_string)) <= 0)
    g_serv.stop(2);

	bzero(&g_serv.addr, sizeof(g_serv.addr));
	g_serv.addr.sin_family = AF_INET; 
	g_serv.addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	g_serv.addr.sin_port = htons(port);

  if ((bind(g_serv.fd, (const struct sockaddr *)&g_serv.addr, sizeof(g_serv.addr))) != 0)
    g_serv.stop(2);
	if (listen(g_serv.fd, 10) != 0)
    g_serv.stop(2);
}

void clear_set() {
  fd_set *set = &g_serv.readset;
  g_serv.max_fd = g_serv.fd;
  t_client *clients = g_serv.clients;

  FD_ZERO(set);
  FD_SET(g_serv.fd, set);
  if (!clients)
    return ;
  while (clients) {
    FD_SET(clients->fd, set);
    if (clients->fd > g_serv.max_fd)
      g_serv.max_fd = clients->fd;
    clients = clients->next;
  }
}

void add_client() {
  printf("ADD CLIENT FUNCTION EXECUTE\n");
  t_client *clients = g_serv.clients;
  t_client *client;
  unsigned int len;

  if (!(client = (t_client *)calloc(1, sizeof(t_client))))
    g_serv.stop(3);

  len = sizeof(client->addr);
  client->fd = accept(g_serv.fd, (struct sockaddr *)&client->addr, &len);
  client->id = g_serv.auto_id++;
  if (client->fd < 0)
    g_serv.stop(3);
  if (!clients) {
    g_serv.clients = client;
    return ;
  } else {
    while (clients->next)
      clients = clients->next;
    clients->next = client;
  }
  g_serv.send_all(client, NULL, 1);
}

void remove_client(int remove_fd) {
  printf("REMOVE CLIENT FUNCTION EXECUTE\n");
  t_client *clients = g_serv.clients;
  t_client *tmp;

  if (!clients)
    return ;

  if (clients->fd == remove_fd) {
    close(clients->fd);
    free(clients);
    g_serv.clients = NULL;
  } else {
    tmp = clients;
    clients = clients->next;
    while (clients && clients->fd != remove_fd) {
      tmp = clients;
      clients = clients->next;
    }
    if (clients->fd == remove_fd) {
      tmp->next = clients->next;
      close(clients->fd);
      free(clients);
      g_serv.send_all(clients, NULL, 2);
    }
  }
  
}

int get_message(char* message, char *buff) {
  int idx = 0;
  char buf[4200];
  int res = 0;

  while (buff && buff[idx] && buff[idx] != '\n')
    ++idx;
  if (buff[idx] == '\n') {
    buff[idx] = '\0';
    res = buff[idx + 1] != '\0' ? 1 : 0;
  }
  strcpy(message, buff);
  message[idx] = '\0';
  bzero(buf, 4200);
  strcpy(buf, &buff[idx + 1]);
  bzero(buff, 4200);
  strcpy(buff, buf);

  return (res);
}

void broadcast() {
  t_client *clients = g_serv.clients;
  t_client *client;

  int count;
  char buff[4200];
  char msg[4200];

  while (clients) {
    client = clients;
    clients = clients->next;
    if (!FD_ISSET(client->fd, &g_serv.readset))
      continue;
    bzero(msg, sizeof(msg));
    bzero(buff, sizeof(buff));
    count = recv(client->fd, buff, 4096, 0);
    if (count == 0)
      g_serv.remove_client(client->fd);
    else {
      while (get_message(msg, buff)) {
        send_all(client, msg, 0);
      }
      send_all(client, msg, 0);
    }
  }
}

void start_server() {
  int server_running = 1;
  struct timeval timeout;
  int count = 0;

  timeout.tv_sec = 5;
  timeout.tv_usec = 0;

  while (server_running) {
    g_serv.clear_set();
    count = select(g_serv.max_fd + 1, &g_serv.readset, NULL, NULL, &timeout);
    if (count <= 0)
      continue;
    if (FD_ISSET(g_serv.fd, &g_serv.readset))
      g_serv.add_client();
    else
      g_serv.broadcast();
  }
}

void initialize() {
  g_serv.connect_server = connect_server;
  g_serv.start = start_server;
  g_serv.clear_set = clear_set;
  g_serv.add_client = add_client;
  g_serv.remove_client = remove_client;
  g_serv.broadcast = broadcast;
  g_serv.send_all = send_all;
  g_serv.stop = stop_server;

  g_serv.clients = NULL;
  g_serv.auto_id = 0;
  g_serv.max_fd = 0;
}

int main(int ac, char *av[]) {

  initialize();
  
  if (ac != 2)
    g_serv.stop(1);

  g_serv.connect_server(av[1]);
  g_serv.start();
  return (0);
}
