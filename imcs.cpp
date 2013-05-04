#include "imcs.h"

static char buffer[1024];



Imcs::Imcs()
{
  verbose = true;
  char hostname[] = "imcs.svcs.cs.pdx.edu";
  int port = 3589;
  char username[] = "chesster";
  char password[] = "chessterspassword";
  char color = 'W';

  // Connect to server
  imcs_connect(hostname, port);

  // Get initial response
  char * init = get();
  if(strncmp(init, "100 imcs 2.5", 12) != 0) {
    perror("This server is not who it claims to be.");
    exit(1);
  }
  
  signin(username, password);
}



Imcs::~Imcs()
{
  fclose(socket_fd);
}



void Imcs::imcs_connect(char * hostname, int port)
{
  ////////// Create host entity //////////
  struct hostent *host = gethostbyname(hostname);
  if (!host) {
    herror("gethostbyname");
    exit(1);
  }
  if (verbose) {
    cout << "made a host" << endl;
  }

  ////////// Create socket //////////
  int sock = socket(host->h_addrtype, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("socket");
    exit(1);
  }
  if (verbose) {
    cout << "made a socket" << endl;
  }

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
  socket_fd = fdopen(sock, "a+");
  if (!socket_fd) {
    perror("couldn't open socket");
    exit(1);
  }
  // setlinebuf sets buffer so that "characters are saved up until a newline is output or input is read from any stream attached to a terminal device"
  setlinebuf(socket_fd);
}



void Imcs::signin(char * username, char * password)
{
  sprintf(buffer, "me %s %s", username, password);
  send(buffer);
  get(); //server sends "hello chesster"
}



void Imcs::offer(char color)
{
  sprintf(buffer, "offer %c", color);
  send(buffer);
  get();
}



void Imcs::game_start()
{
  //TODO: error checking, make sure these are getting what we expect
  get();
  get();
}



// TODO: make this work
void Imcs::join(int game_id)
{
}


void Imcs::make_move(Move local_move)
{
  // Assumes error checking before function call
  send(local_move.to_s());
}

Move Imcs::get_move()
{
  char * imcs_move = get();
  (void) strtok(imcs_move, " ");
  char * stringmove = strtok(NULL, "\n");
  char * valid_move = new char[strlen(stringmove)];
  strncpy(valid_move, stringmove, strlen(stringmove) - 1);
  if (!move_is_valid(valid_move)) {
    cout << stringmove << endl;
    perror("received invalid string for move");
    exit(1);
  }
  Move remote_move = Move(stringmove);
  remote_move.print();
  return remote_move;
}

// private
char * Imcs::get()
{
  if (verbose) {
    cout << "attempting to get response" << endl;
  }
  char * resp = fgets(buffer, sizeof(buffer), socket_fd);
  if (!resp || strlen(resp) >= sizeof(buffer) - 1) {
    perror("Failed to get something from the server");
    exit(1);
  }
  if (verbose) {
    cout << "got response: " << resp << endl;
  }
  return resp;
}



void Imcs::send(char * command)
{
  if(fprintf(socket_fd, "%s\n", command) == -1) {
    perror("Failed to send command");
    exit(1);
  }
  if (verbose) {
    cout << "sent command: " << command << endl;
  }
}
