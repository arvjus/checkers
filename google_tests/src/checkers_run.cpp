/* Copyright (c) 2022, Arvid Juskaitis (arvydas.juskaitis@gmail.com)

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1335  USA */

#include "game.h"
#include "minmax_agent.h"
#include "alphabeta_agent.h"
#include "utils.h"
#include "random_agent.h"

int main(int argc, char** argv) {
  std::unique_ptr game = std::make_unique<Game>(true);
  game->set_player_turn(Player::Black);

  AlphabetaAgent agent1(5, 2, Player::Black);
  AlphabetaAgent agent2(5, 2, Player::White);
//  RandomAgent agent2(Player::White);

  for (auto i = 0; i < 1000 && !game->is_over(); i++) {
    auto moves = game->get_board().get_possible_moves();
    if (game->whose_turn() == Player::Black) {
      if (!moves.empty()) {
        auto move = agent1.next_move(game);
        game->move(move.first);
      }
    } else {
      if (!moves.empty()) {
        auto move = agent2.next_move(game);
        game->move(move.first);
      }
    }
  }
  assert(game->is_over());
  game->print_status();
}
