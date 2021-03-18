#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct	    s_client
{
	int					        fd;
	int					        id;
  struct sockaddr_in  addr;
	struct s_client*	  next;
}				            t_client;

typedef struct s_server
{
  int                 fd;
  int                 max_fd;
  struct sockaddr_in  addr;
  fd_set              readset;
  t_client            *clients;
  int                 auto_id;
  char                buff[4200];

  void (*connect)(char *);
  void (*clear_set)();
  void (*speak)(int, char *, int);
  void (*add_client)();
  void (*remove_client)(int);
  void (*broadcast)();
  void (*start)();
}              t_server;

t_server g_serv;

void ft_exit(int type) {
  char *argument_error = "Wrong number of arguments\n";
  char *fatal_error = "Fatal error\n";
  t_client *client = g_serv.clients;
  t_client *tmp;
  int fd;

  if (type == 1)
    write(2, argument_error, strlen(argument_error));
  else if (type > 1)
    write(2, fatal_error, strlen(fatal_error));

  if (type > 2) {
    while (client != NULL) {
      tmp = client;
      fd = client->fd;
      client = client->next;
      close(fd);
      free(tmp);
    }
    if (g_serv.clients)
      free(g_serv.clients);
  }
  if (type != 1)
    close(g_serv.fd);

  exit(type == 0 ? 0 : 1);
}

void connect_server(char *port_str) {
  int port;

  if ((g_serv.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    ft_exit(2);
  bzero(&g_serv.addr, sizeof(g_serv.addr));
  if ((port = atoi(port_str)) <= 0)
    ft_exit(2);
  g_serv.addr.sin_family = AF_INET; 
	g_serv.addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	g_serv.addr.sin_port = htons(port);

	if ((bind(g_serv.fd, (const struct sockaddr *)&g_serv.addr, sizeof(g_serv.addr))) != 0)
    ft_exit(2);
	if (listen(g_serv.fd, 10) != 0)
    ft_exit(2);
};

void clear_set() {
  fd_set *set;
  int max_fd;
  t_client *clients;
  
  set = &g_serv.readset;
  FD_ZERO(set);
  max_fd = g_serv.fd;
  clients = g_serv.clients;
  
  while (clients != NULL) {
    FD_SET(clients->fd, set);
    if (max_fd < clients->fd)
      max_fd = clients->fd;
    clients = clients->next;
  }
  FD_SET(g_serv.fd, set);
  g_serv.max_fd = max_fd;
}

void speak(int send_id, char *msg, int type) {

  printf("speak request: %d: %s: %d\n", send_id, msg, type);
  t_client *clients = g_serv.clients;
  char message[4200];

  while (clients) {
    if (clients->fd != send_id) {
      bzero(message, 4200);
      if (msg != NULL)
        sprintf(message, "client %d: %s\n", clients->fd, msg);
      else if (type == 1)
        sprintf(message, "server: client %d just arrived\n", clients->fd);
      else if (type == 2)
        sprintf(message, "server: client %d just left\n", clients->fd);
      printf("speak execute: %d: %s: %d\n", clients->fd, message, clients->fd);
      send(clients->fd, message, strlen(message), 0);
    }
    clients = clients->next;
  }
}

void add_client() {
  t_client *clients = g_serv.clients;
  t_client *client;
  int size;
  int fd;

  if ((client = calloc(1, sizeof(t_client))) == NULL)
    ft_exit(3);
  size = sizeof(client->addr);
  if ((client->fd = accept(g_serv.fd, (struct sockaddr *)&client->addr, (unsigned int*)&size)) < 0)
    return;
  if (!clients)
    g_serv.clients = client;
  else {
    while (clients->next)
      clients = clients->next;
    clients->next = client;
  }
  if (g_serv.clients && g_serv.clients->next)
  printf("clients: %p | next: %p | id: %d\n", g_serv.clients, g_serv.clients->next, client->fd);

  g_serv.speak(client->fd, NULL, 1);
}

void remove_client(int remove_fd) {
  t_client *clients = g_serv.clients;
  t_client *prev = NULL;

  if (clients == NULL)
    return ;
  if (clients->fd == remove_fd) {
    close(remove_fd);
    free(clients);
    speak(remove_fd, NULL, 2);
    return ;
  }

  prev = clients;
  clients = clients->next;
  while (clients != NULL) {
    if (clients->fd == remove_fd) {
      prev->next = clients->next;
      close(remove_fd);
      free(clients);
      speak(remove_fd, NULL, 2);
      return ;
    }
    prev = clients;
    clients = clients->next;
  }
}

int get_message(char *buff) {
  char tmp[4200];
  int idx = 0;
  int res;

  while (g_serv.buff[idx] && g_serv.buff[idx] != '\n')
    ++idx;
  res = g_serv.buff[idx + 1] != '\0' ? 1 : 0;
  g_serv.buff[idx] = '\0';
  strcpy(buff, g_serv.buff);
  if (!res)
    return res;
  bzero(tmp, 4200);
  strcpy(tmp, &buff[idx + 1]);
  bzero(buff, 4200);
  strcpy(buff, tmp);
  return res;
}

void broadcast() {
  t_client *clients = g_serv.clients;
  fd_set *readset = &g_serv.readset;
  int fd, id, read_count;
  char buff[4200];

  while (clients) {
    fd = clients->fd;
    id = clients->id;
  
    clients = clients->next;
    if (!FD_ISSET(fd, readset))
      continue;
    bzero(g_serv.buff, 4200);
    read_count = recv(fd, g_serv.buff, 4096, 0);
    if (read_count == 0)
      g_serv.remove_client(fd);
    else if (read_count > 0) {
      while (get_message(buff))
        speak(id, buff, 0);
      speak(id, buff, 0);
    }
  }
}

void start_server() {
  int server_running;
  int count;
  struct timeval timeout;

  timeout.tv_sec = 5;
  timeout.tv_usec = 0;

  server_running = 1;
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
  g_serv.clients = NULL;
  g_serv.connect = connect_server;
  g_serv.clear_set = clear_set;
  g_serv.add_client = add_client;
  g_serv.remove_client = remove_client;
  g_serv.broadcast = broadcast;
  g_serv.start = start_server;
  g_serv.speak = speak;
  g_serv.auto_id = 0;
}

int main(int ac, char *av[]) {

  if (ac != 2)
    ft_exit(1);

  initialize();

  g_serv.connect(av[1]);
  g_serv.start();

  return (0);
}
