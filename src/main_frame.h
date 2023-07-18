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
