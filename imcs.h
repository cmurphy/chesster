#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "header.h"

class Imcs
{
  public:
    Imcs();
    ~Imcs();
    void imcs_connect(char * hostname, int port);
    void signin(char * username, char * password);
    void offer(char color);
    void join(int game_id);
    void make_move(Move local_move);
    Move get_move();
    void game_start();
  private:
    void send(char * command);
    char * get();
    FILE * socket_fd;
    bool verbose;
};
