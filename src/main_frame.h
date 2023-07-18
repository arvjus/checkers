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

#pragma once

#include <memory>
#include <array>
#include <wx/wx.h>
#include "board_panel.h"
#include "game.h"
#include "agent.h"

enum MenuCmd {
  MenuCmdGameBlackBegins = 1,
  MenuCmdGameWhiteBegins,
  MenuCmdGameUndo,
  MenuCmdGameQuit,
  MenuCmdOpponentHuman,
  MenuCmdOpponentMachine,
  MenuCmdOpponentShowScores,
  MenuCmdOpponentHeuristic,
  MenuCmdOpponentAlphabeta1,
  MenuCmdOpponentAlphabeta2,
  MenuCmdOpponentAlphabeta3,
  MenuCmdBoardCustom,
  MenuCmdBoardBlackMan,
  MenuCmdBoardBlackKing,
  MenuCmdBoardWhiteMan,
  MenuCmdBoardWhiteKing,
  MenuCmdBoardEmpty,
  MenuCmdBoardOpen,
  MenuCmdBoardSave,
  MenuCmdBoardSaveAs,
  MenuCmdHelpAbout,
  MenuCmdTotalItems
};

class MainFrame : public wxFrame {
public:
  MainFrame();
  void handleKeyEvent(wxKeyEvent& event);
  void handleMouseClickOnPosition(Pos pos);

private:
  std::unique_ptr<Game> game = std::make_unique<Game>();
  Pos selection;
  std::vector<Pos> valid_positions;
  wxMenuBar* mainMenu = new wxMenuBar();
  BoardPanel* boardPanel = new BoardPanel(this, game, selection, valid_positions);
  wxStatusBar* statusBar = new wxStatusBar(this);
  std::array<wxMenuItem*, MenuCmdTotalItems> menuItems;
  bool customSetupMode = false;
  bool humanVsHumanMode = false;
  std::vector<std::shared_ptr<Agent>> agents;

  void initMenuItems();
  void enableMenuItems();
  void handleMenuEvent(wxCommandEvent& event);
  void enterCustomSetupMode();
  void doCustomPlacements(Pos pos);
  void restartGame(Player player);
  void updateStatus();
  void humanMoveNext(Pos pos);
  void machineMoveNext();
  void showAboutDialog();
  void undoMove();
  void saveBoard(bool b);
  void openBoard(bool b);
  void print_scores(const best_move_with_scores& best_move) const;
};
