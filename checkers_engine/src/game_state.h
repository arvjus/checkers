#pragma once

#include <array>
#include "board.h"

class Game;
class GameState {
public:
  GameState(Game& g);
  GameState& operator =(const GameState& g);
  void restore();

private:
  Game& game;
  Board board;
  std::uint16_t move_count;
  std::uint16_t move_count_since_last_capture;
};

template<typename T, int max_limit>
class vector_with_max_limit : public std::vector<T> {
public:
  void push_back_limited(const T& item) {
    if (std::vector<T>::size() >= max_limit)
      std::vector<T>::erase(std::vector<T>::begin());
    std::vector<T>::push_back(item);
  }
};
using game_state_vector = vector_with_max_limit<GameState, UNDO_MOVE_LIMIT>;

