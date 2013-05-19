#ifndef IMCS_H
#define IMCS_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>

class Move;

class Imcs
{
  public:
    Imcs(bool verbose);
    ~Imcs();
    void imcs_connect(char * hostname, int port);
    void signin(char * username, char * password);
    void offer(char color);
    void accept(int game, char color);
    void join(int game_id);
    void make_move(Move local_move);
    Move get_move();
    void get_board();
    char game_start(char player_color);
  private:
    void send(char * command);
    char * get();
    FILE * socket_fd;
    bool verbose;
};

#endif
