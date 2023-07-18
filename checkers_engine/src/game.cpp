#include <stack>
#include <iostream>
#include "game.h"

Game::Game(bool with_starting_pieces)
    : board(with_starting_pieces) {
}

void Game::move(const Move& move) {
  if (board.whose_turn() == Player::White)
    move_history.push_back_limited(GameState(*this));

  move_count++;
  if (move.is_capture_move()) {
    board.perform_capture_move(move);
    move_count_since_last_capture = 0;
  } else {
    board.perform_positional_move(move);
    move_count_since_last_capture++;
  }
}

bool Game::undo_move() {
  if (move_history.empty())
    return false;

  auto game_state = move_history.back();
  game_state.restore();
  move_history.pop_back();
  return true;
}

bool Game::is_over() const {
  return move_limit_reached() || board.count_movable_player_pieces(board.whose_turn()) == 0;
}

Player Game::get_winner() const {
  auto no_b = board.count_movable_player_pieces(Player::Black) == 0;
  auto no_w = board.count_movable_player_pieces(Player::White) == 0;
  return (no_b == no_w) ? Player::Undef : no_b ? Player::White : Player::Black;
}

std::vector<Pos> Game::get_available_positions_from(Pos pos) const {
  std::vector<Pos> positions;
  auto possible_moves = board.get_possible_moves();
  for (auto move : possible_moves)
    if (move.src == pos)
      positions.push_back(move.dst);
  return positions;
}

GamePhase Game::get_game_phase() const {
  auto counts = board.count_available_inventory(Player::Black);
  return std::min(get<0>(counts) + get<1>(counts),
                  get<2>(counts) + get<3>(counts)) < 3
             ? GamePhase::END_GAME
             : GamePhase::OPENING_MIDDLE_GAME;
}

void Game::print_status() const {
  std::cout << "is_over=" << is_over()
            << ", winner=" << (int) get_winner()
            << ", moves=" << move_count
            << ", black=" << get_board().get_available_inventory(Player::Black).size()
            << ", white=" << get_board().get_available_inventory(Player::White).size()
            << std::endl;
}

