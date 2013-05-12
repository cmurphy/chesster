#include "game.h"
#include "player.h"
#include "state.h"
#include "imcs.h"
#include "move.h"


Game::Game(char player_color, bool verbose)
{
  player = new Player(player_color);
  board = new State;
  server = new Imcs(verbose);
  server->offer('W');
}



Game::~Game()
{
  delete player;
  delete board;
  delete server;
}



void Game::play()
{
  char self_color = player->get_color();
  cout << "self color" << self_color << endl;
  cout << "Waiting for game to be accepted" << endl;
  server->game_start(self_color);
  while (!board->game_is_over()) {
    if (player->get_color() == 'W') { //If white, go first
      server->get_board();
      Move local_move = player->choose_move(*board);
      *board = board->make_move(local_move);
      cout << "Sending move to server (white)" << endl;
      server->make_move(local_move);
      if (board->game_is_over()) {
        break;
      }
      board->update_side_on_move();
      cout << "Waiting for move from server (white)" << endl;
      Move remote_move = server->get_move(); // TODO: error checking for legality of remote move
      cout << "Received move " << remote_move << endl;
      *board = board->make_move(remote_move); 
      board->update_side_on_move();
      board->update_move_count();
    }
    else {
      cout << "Waiting for move from server (black)" << endl;
      Move remote_move = server->get_move(); 
      cout << "Received move " << remote_move << endl;
      *board = board->make_move(remote_move); 
      if (board->game_is_over()) {
        break;
      }
      Move local_move = player->choose_move(*board);
      *board = board->make_move(local_move);
      server->make_move(local_move);
    }
  }
}
