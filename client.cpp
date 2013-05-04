#include "header.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

FILE * connect_host(char * hostname, int port)
{
  ////////// Create host entity //////////
  struct hostent *host = gethostbyname(hostname);
  if (!host) {
    herror("gethostbyname");
    exit(1);
  }
  cout << "made a host" << endl;

  ////////// Create socket //////////
  int sock = socket(host->h_addrtype, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("socket");
    exit(1);
  }
  cout << "made a socket" << endl;

  ////////// Try addresses //////////
  char ** addr;
  for (addr = host->h_addr_list; *addr; ++addr) { // addr gets first addr in list; addr is dereferenceable; increment addr
    struct sockaddr_in socket_address;
    socket_address.sin_family = host->h_addrtype;
    socket_address.sin_port = htons(port);
    memcpy(&socket_address.sin_addr, *addr, host->h_length);
    if (connect(sock, (struct sockaddr *)&socket_address, sizeof(socket_address)) != -1) {
      cout << "connected to a socket" << endl;
      break;
    }
  }
  // Didn't connect
  if (!*addr) {
    perror("couldn't connect");
    exit(1);
  }

  // Open socket for appending
  FILE * socket_handle = fdopen(sock, "a+");
  if (!socket_handle) {
    perror("couldn't open socket");
    exit(1);
  }
  // setlinebuf sets buffer so that "characters are saved up until a newline is output or input is read from any stream attached to a terminal device"
  setlinebuf(socket_handle);
  return socket_handle;
}

static char buffer[1024];
char * get_response(FILE * socket_handle)
{
  cout << "attempting to get response" << endl;
  char * resp = fgets(buffer, sizeof(buffer), socket_handle);
  if (!resp || strlen(resp) >= sizeof(buffer) - 1) {
    perror("Failed to get something from the server");
    exit(1);
  }
  cout << "got response" << endl;
  return resp;
}

void send_command(FILE * socket_handle, char * command)
{
  sprintf(buffer, "help");
  if(fprintf(socket_handle, "%s\n", buffer) == -1) {
    perror("Failed to send command");
    exit(1);
  }
  cout << "sent command" << endl;
}

int main()
{
  char IMCS_HOST[] = "imcs.svcs.cs.pdx.edu";
  int IMCS_PORT = 3589;

  FILE * netfile = connect_host(IMCS_HOST, IMCS_PORT);
  char * response = get_response(netfile);
  cout << response << endl;
  char command[] = "help";
  fflush(stdout);
  send_command(netfile, command);
  char * response2 = get_response(netfile);
  cout << response2 << endl;

  return 0;
}
