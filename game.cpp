#include "game.h"
#include "player.h"
#include "state.h"
#include "imcs.h"
#include "move.h"


Game::Game(bool player_color)
{
  player = new Player(player_color);
  board = new State;
  server = new Imcs;
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
  cout << "Waiting for game to be accepted" << endl;
  server->game_start();
  while (!board->game_is_over()) {
    if (player->get_color()) { //If white, go first
      Move local_move = player->choose_move(*board);
      *board = board->make_move(local_move);
      server->make_move(local_move);
      if (board->game_is_over()) {
        break;
      }
      board->update_side_on_move();
      Move remote_move = server->get_move(); // TODO: error checking for legality of remote move
      *board = board->make_move(remote_move); 
      board->update_side_on_move();
    }
    else {
      Move remote_move = server->get_move(); 
      *board = board->make_move(remote_move); 
      if (board->game_is_over()) {
        break;
      }
      Move local_move = player->choose_move(*board);
      *board = board->make_move(local_move);
    }
  }
}
