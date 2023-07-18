#include "game_state.h"
#include "game.h"

GameState::GameState(Game& g)
    : game(g), board(g.board),
      move_count(g.move_count),
      move_count_since_last_capture(g.move_count_since_last_capture) {
}

GameState& GameState::operator=(const GameState& g) {
  board = g.board;
  move_count = g.move_count;
  move_count_since_last_capture = g.move_count_since_last_capture;
  return *this;
}

void GameState::restore() {
  game.board = board;
  game.move_count = move_count;
  game.move_count_since_last_capture = move_count_since_last_capture;
}
