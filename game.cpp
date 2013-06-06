#include "game.h"
#include "player.h"
#include "state.h"
#include "imcs.h"
#include "move.h"


Game::Game(char player_color, bool verbose, bool offer, int game)
{
  player = new Player(player_color);
  board = new State;
  server = new Imcs(verbose);
  if (offer) {
    server->offer(player_color);
  } else {
    server->accept(game, player_color);
  }
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
  self_color = server->game_start(self_color);
  player->set_color(self_color);
  while (!board->game_is_over()) {
    if (player->get_color() == 'W') { //If white, go first
      server->get_board();
      Move local_move = player->choose_move(*board);
      board->make_move(local_move);
      server->make_move(local_move);
      if (board->game_is_over()) {
        break;
      }
      board->update_side_on_move();
      board->print();
      cout << endl << endl;
      Move remote_move = server->get_move(); // TODO: error checking for legality of remote move
      board->make_move(remote_move); 
      board->update_side_on_move();
      board->update_move_count();
      board->print();
      cout << endl << endl;
    }
    else {
      Move remote_move = server->get_move(); 
      server->get_board();
      board->make_move(remote_move); 
      board->update_side_on_move();
      board->print();
      cout << endl << endl;
      if (board->game_is_over()) {
        break;
      }
      Move local_move = player->choose_move(*board);
      board->make_move(local_move);
      server->make_move(local_move);
      board->update_side_on_move();
      board->update_move_count();
      board->print();
      cout << endl << endl;
    }
  }
}
