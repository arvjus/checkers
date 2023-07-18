#include <cstdlib>
#include <climits>
#include <chrono>
#include <thread>
#include <wx/aboutdlg.h>
#include <checkers_config.h>
#include "checkers.xpm"
#include "main_frame.h"
#include "utils.h"
#include "snapshot.h"
#include "random_agent.h"
#include "first_move_agent.h"
#include "heuristic_agent.h"
#include "alphabeta_agent.h"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Checkers", wxDefaultPosition, wxDefaultSize,
              wxSYSTEM_MENU | wxRESIZE_BORDER | wxMINIMIZE_BOX | wxCLOSE_BOX), selection(Pos::none) {
  SetIcon(checkers_xpm);
  initMenuItems();

  // init status bar
  SetStatusBar(statusBar);
  std::vector statusWidths = {615, -1};
  std::vector statusStyles = {wxSB_NORMAL, wxSB_NORMAL};
  statusBar->SetFieldsCount(static_cast<int>(statusWidths.size()));
  statusBar->SetStatusWidths(static_cast<int>(statusWidths.size()), statusWidths.data());
  statusBar->SetStatusStyles(static_cast<int>(statusStyles.size()), statusStyles.data());
  updateStatus();

  // set size
  SetClientSize({BoardPanel::WIDTH + BoardPanel::MARGIN * 2,
                 BoardPanel::HEIGHT + BoardPanel::MARGIN * 3 +
                 mainMenu->GetMaxHeight() + statusBar->GetMaxHeight()});
  SetMinSize(GetSize());
  SetMaxSize(GetSize());

  Player player = menuItems[MenuCmdGameBlackBegins]->IsChecked() ? Player::Black : Player::White;
  game->set_player_turn(player);
  updateStatus();

  std::srand(std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count());
}

void MainFrame::initMenuItems() {
  auto menuGame = new wxMenu();
  menuItems[MenuCmdGameBlackBegins] = menuGame->Append(MenuCmdGameBlackBegins, "Black begins\tB", "", wxITEM_RADIO);
  menuItems[MenuCmdGameWhiteBegins] = menuGame->Append(MenuCmdGameWhiteBegins, "White begins\tW", "", wxITEM_RADIO);
  menuGame->AppendSeparator();
  menuItems[MenuCmdGameUndo] = menuGame->Append(MenuCmdGameUndo, "Undo move\tU");
  menuGame->AppendSeparator();
  menuItems[MenuCmdGameQuit] = menuGame->Append(MenuCmdGameQuit, "Quit\tCtrl+Q");
  mainMenu->Append(menuGame, "Game");

  auto menuOpponent = new wxMenu();
  menuItems[MenuCmdOpponentMachine] = menuOpponent->Append(MenuCmdOpponentMachine, "Machine\tM", "", wxITEM_RADIO);
  menuItems[MenuCmdOpponentHuman] = menuOpponent->Append(MenuCmdOpponentHuman, "Human\tH", "", wxITEM_RADIO);
  menuOpponent->AppendSeparator();
  menuItems[MenuCmdOpponentShowScores] = menuOpponent->Append(MenuCmdOpponentShowScores, "Show scores", "Explain move decisions", wxITEM_CHECK);
  menuOpponent->AppendSeparator();
  menuItems[MenuCmdOpponentHeuristic] = menuOpponent->Append(MenuCmdOpponentHeuristic, "Basic", "Just following the rules", wxITEM_RADIO);
  menuItems[MenuCmdOpponentAlphabeta1] = menuOpponent->Append(MenuCmdOpponentAlphabeta1, "Easy", "Look ahead 4 moves", wxITEM_RADIO);
  menuItems[MenuCmdOpponentAlphabeta2] = menuOpponent->Append(MenuCmdOpponentAlphabeta2, "Medium", "Look ahead 8 moves, 10 sec time limit", wxITEM_RADIO);
  menuItems[MenuCmdOpponentAlphabeta3] = menuOpponent->Append(MenuCmdOpponentAlphabeta3, "Hard", "Look ahead 8 moves, 30 sec time limit", wxITEM_RADIO);
  menuItems[MenuCmdOpponentAlphabeta2]->Check(true);
  mainMenu->Append(menuOpponent, "Opponent");

  auto menuBoard = new wxMenu();
  menuItems[MenuCmdBoardCustom] = menuBoard->Append(MenuCmdBoardCustom, "Custom setup\tC");
  menuItems[MenuCmdBoardBlackMan] = menuBoard->Append(MenuCmdBoardBlackMan, "Black man\tAlt+B", "", wxITEM_RADIO);
  menuItems[MenuCmdBoardBlackKing] = menuBoard->Append(MenuCmdBoardBlackKing, "Black king\tAlt+Shift+B", "", wxITEM_RADIO);
  menuItems[MenuCmdBoardWhiteMan] = menuBoard->Append(MenuCmdBoardWhiteMan, "White man\tAlt+W", "", wxITEM_RADIO);
  menuItems[MenuCmdBoardWhiteKing] = menuBoard->Append(MenuCmdBoardWhiteKing, "White king\tAlt+Shift+W", "", wxITEM_RADIO);
  menuItems[MenuCmdBoardEmpty] = menuBoard->Append(MenuCmdBoardEmpty, "Empty\tAlt+e", "", wxITEM_RADIO);
  menuBoard->AppendSeparator();
  menuItems[MenuCmdBoardOpen] = menuBoard->Append(MenuCmdBoardOpen, "Open...\tCtrl+O");
  menuItems[MenuCmdBoardSave] = menuBoard->Append(MenuCmdBoardSave, "Save\tCtrl+S");
  menuItems[MenuCmdBoardSaveAs] = menuBoard->Append(MenuCmdBoardSaveAs, "Save as...\tShift+Ctrl+S");
  mainMenu->Append(menuBoard, "Board");

  auto menuHelp = new wxMenu();
  menuItems[MenuCmdHelpAbout] = menuHelp->Append(MenuCmdHelpAbout, "&About");
  mainMenu->Append(menuHelp, "Help");
  SetMenuBar(mainMenu);
  enableMenuItems();
  Bind(wxEVT_MENU, & MainFrame::handleMenuEvent, this);
}

void MainFrame::enableMenuItems() {
  auto menuCmdOpponentComputer = menuItems[MenuCmdOpponentMachine]->IsChecked();
  menuItems[MenuCmdOpponentHeuristic]->Enable(menuCmdOpponentComputer);
  menuItems[MenuCmdOpponentAlphabeta2]->Enable(menuCmdOpponentComputer);
  menuItems[MenuCmdOpponentAlphabeta1]->Enable(menuCmdOpponentComputer);
  menuItems[MenuCmdOpponentAlphabeta3]->Enable(menuCmdOpponentComputer);

  menuItems[MenuCmdBoardBlackMan]->Enable(customSetupMode);
  menuItems[MenuCmdBoardBlackKing]->Enable(customSetupMode);
  menuItems[MenuCmdBoardWhiteMan]->Enable(customSetupMode);
  menuItems[MenuCmdBoardWhiteKing]->Enable(customSetupMode);
  menuItems[MenuCmdBoardEmpty]->Enable(customSetupMode);
}

void MainFrame::handleMenuEvent(wxCommandEvent& event) {
  switch (event.GetId()) {
  case MenuCmdGameQuit:
    Close(true);
    break;
  case MenuCmdGameBlackBegins:
    restartGame(Player::Black);
    break;
  case MenuCmdGameWhiteBegins:
    restartGame(Player::White);
    break;
  case MenuCmdGameUndo:
    undoMove();
    break;
  case MenuCmdOpponentHuman:
    humanVsHumanMode = true;
    enableMenuItems();
    break;
  case MenuCmdOpponentMachine:
    humanVsHumanMode = false;
    enableMenuItems();
    break;
  case MenuCmdBoardCustom:
    enterCustomSetupMode();
    enableMenuItems();
    break;
  case MenuCmdBoardSave:
    saveBoard(false);
    break;
  case MenuCmdBoardSaveAs:
    saveBoard(true);
    break;
  case MenuCmdBoardOpen:
    openBoard(false);
    break;
  case MenuCmdHelpAbout:
    showAboutDialog();
    break;
  default:
    event.Skip();
  }
}

void MainFrame::handleMouseClickOnPosition(Pos pos) {
  if (customSetupMode) {
    doCustomPlacements(pos);
  } else if (humanVsHumanMode || game->whose_turn() == Player::White) {
    humanMoveNext(pos);
  }

  if (!humanVsHumanMode && game->whose_turn() == Player::Black) {
    machineMoveNext();
  }
}

void MainFrame::handleKeyEvent(wxKeyEvent& event) {
  auto key = event.GetKeyCode();
  if (key != WXK_NONE) {
    if (event.ControlDown() && (key == 'q' || key == 'Q'))
      Close(true);
    if (event.AltDown()) {
      if (key == 'b')
        menuItems[MenuCmdBoardBlackMan]->Check();
      else if (key == 'B')
        menuItems[MenuCmdBoardBlackKing]->Check();
      else if (key == 'w')
        menuItems[MenuCmdBoardWhiteMan]->Check();
      else if (key == 'W')
        menuItems[MenuCmdBoardWhiteKing]->Check();
      else if (key == 'e')
        menuItems[MenuCmdBoardEmpty]->Check();
    } else if (key == 'b' || key == 'B') {
      menuItems[MenuCmdGameBlackBegins]->Check();
      restartGame(Player::Black);
    } else if (key == 'w' || key == 'W') {
      menuItems[MenuCmdGameWhiteBegins]->Check();
      restartGame(Player::White);
    } else if (key == 'u' || key == 'U') {
      undoMove();
    } else if (key == 'h' || key == 'H') {
      menuItems[MenuCmdOpponentHuman]->Check();
      humanVsHumanMode = true;
      enableMenuItems();
    } else if (key == 'm' || key == 'M') {
      menuItems[MenuCmdOpponentMachine]->Check();
      humanVsHumanMode = false;
      enableMenuItems();
    } else if (key == 'c')
      enterCustomSetupMode();
  }
  event.Skip();
}

void MainFrame::enterCustomSetupMode() {
  customSetupMode = true;
  menuItems[MenuCmdBoardBlackMan]->Check();
  game = std::make_unique<Game>(false);
  selection = Pos::none;
  boardPanel->Refresh();
  updateStatus();
}

void MainFrame::doCustomPlacements(Pos pos) {
  Piece piece;
  if (menuItems[MenuCmdBoardBlackMan]->IsChecked())
    piece = Piece(pos, Player::Black);
  else if (menuItems[MenuCmdBoardBlackKing]->IsChecked())
    piece = Piece(pos, Player::Black, true);
  else if (menuItems[MenuCmdBoardWhiteMan]->IsChecked())
    piece = Piece(pos, Player::White);
  else if (menuItems[MenuCmdBoardWhiteKing]->IsChecked())
    piece = Piece(pos, Player::White, true);
  else
    piece = Piece(pos, Player::Undef);
  game->put_piece(piece);
  boardPanel->Refresh();
}

void MainFrame::openBoard(bool b) {
  wxFileDialog openFileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "CSV Files (*.csv)|*.csv|All Files (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
  openFileDialog.SetFilterIndex(0);
  if (openFileDialog.ShowModal() == wxID_OK) {
    std::string path(openFileDialog.GetPath());

    Snapshot snapshot;
    snapshot.open(path);
    game = std::make_unique<Game>(false);
    game->init_board(snapshot.get_pieces());
    game->set_player_turn(snapshot.whose_turn());
    customSetupMode = true;
    selection = Pos::none;
    boardPanel->Refresh();
    updateStatus();
  }
}
void MainFrame::saveBoard(bool dialog) {
  std::string path;
  if (dialog) {
    wxFileDialog saveFileDialog(this, wxEmptyString, wxEmptyString, "shapshot_0.csv", "CSV Files (*.csv)|*.csv|All Files (*.*)|*.*", wxFD_SAVE);
    if (saveFileDialog.ShowModal() == wxID_OK)
      path = saveFileDialog.GetPath();
    else
      return;
  } else
    path = Snapshot::get_snapshot_name();

  Snapshot snapshot(game->get_board());
  snapshot.save(path);
}

void MainFrame::restartGame(Player player) {
  if (!customSetupMode)
    game = std::make_unique<Game>();

  game->set_player_turn(player);
  selection = Pos::none;

  if (!humanVsHumanMode) {
    agents.clear();
    if (!customSetupMode)
      agents.push_back(std::make_shared<FirstMoveAgent>());

    if (menuItems[MenuCmdOpponentHeuristic]->IsChecked())
      agents.push_back(std::make_shared<HeuristicAgent>(0));
    else
    if (menuItems[MenuCmdOpponentAlphabeta1]->IsChecked())
      agents.push_back(std::make_shared<AlphabetaAgent>(2, 4));
    else
    if (menuItems[MenuCmdOpponentAlphabeta2]->IsChecked())
      agents.push_back(std::make_shared<AlphabetaAgent>(10, 7));
    else
    if (menuItems[MenuCmdOpponentAlphabeta3]->IsChecked())
      agents.push_back(std::make_shared<AlphabetaAgent>(30, 8));
    else
      agents.push_back(std::make_shared<RandomAgent>());

    if (player == Player::Black)
      machineMoveNext();
  }
  customSetupMode = false;
  enableMenuItems();

  boardPanel->Refresh();
  updateStatus();
}

void MainFrame::updateStatus() {
  if (customSetupMode) {
    wxString text = "Custom setup mode";
    if (game->whose_turn() != Player::Undef)
      text += wxString::Format(", %s's turn", game->whose_turn() == Player::Black ? "black" : "white");
    statusBar->SetStatusText(text, 0);
    statusBar->SetStatusText("", 1);
  } else {
    wxString status = game->is_over() ?
                      wxString::Format("The winner is %s", game->get_winner() == Player::Undef ? "none (draw)" : game->get_winner() == Player::Black ? "black" : "white") :
                      wxString::Format("%s's turn", game->whose_turn() == Player::Black ? "Black" : "White");
    statusBar->SetStatusText(status, 0);

    auto counts = game->get_board().count_available_inventory(Player::Black);
    statusBar->SetStatusText(wxString::Format("B:%-2u W:%-2u",
                                              (INITIAL_NUMBER_OF_PIECES_PER_PLAYER - get<2>(counts) - get<3>(counts)),
                                              (INITIAL_NUMBER_OF_PIECES_PER_PLAYER - get<0>(counts) - get<1>(counts))), 1);
  }
}

void MainFrame::showAboutDialog() {
  wxAboutDialogInfo aboutInfo;
  aboutInfo.SetIcon({checkers_xpm});
  aboutInfo.SetName(wxTheApp->GetAppName());
  aboutInfo.SetVersion(wxString::Format("%d.%d (%d)", checkers_VERSION_MAJOR, checkers_VERSION_MINOR, checkers_BUILD));
  aboutInfo.SetDescription("American Checkers / English Draughts");
  aboutInfo.SetCopyright("Copyright (c) 2022 Arvid Juskaitis\nAll rights reserved.");
  wxAboutBox(aboutInfo, this);
}

void MainFrame::humanMoveNext(Pos pos) {
  assert(humanVsHumanMode || game->whose_turn() == Player::White);

  auto piece = game->get_board().get_piece_at_pos(pos);
  if (piece.get_player() == game->whose_turn()) {
    // making selection
    auto available_for_position = game->get_available_positions_from(pos);
    selection = Pos::none;
    if (!available_for_position.empty()) {
      selection = pos;
      valid_positions = available_for_position;
    }
  } else if (piece.get_player() == Player::Undef && selection != Pos::none && vector_contains(valid_positions, pos)) {
    // making move
    game->move({selection, pos});
    selection = Pos::none;
  }

  boardPanel->Refresh();
  updateStatus();
}

void MainFrame::undoMove() {
  if (game->undo_move()) {
    selection = Pos::none;
    boardPanel->Refresh();
    updateStatus();
  }
}

void MainFrame::machineMoveNext() {
  assert(game->whose_turn() == Player::Black);

  using namespace std::chrono_literals;

  statusBar->SetStatusText("I am thinking...", 0);
  while (game->whose_turn() == Player::Black) {
    best_move_with_scores next_move{Move::none, vector_of_scored_moves()};
    for (auto agent : agents) {
      next_move = agent->next_move(game);
      if (next_move.first != Move::none)
        break;
    }
    if (next_move.first != Move::none) {
      game->move(next_move.first);
      if (menuItems[MenuCmdOpponentShowScores]->IsChecked() && !next_move.second.empty()) {
        print_scores(next_move);
      }
      std::this_thread::sleep_for(500ms);
    }
    else
      break;
  }

  boardPanel->Refresh();
  updateStatus();
}

void MainFrame::print_scores(const best_move_with_scores& best_move) const {
  score min_score = LONG_MAX, max_score = LONG_MIN;
  for (auto scored_move : best_move.second) {
    if (scored_move.first < min_score)
      min_score = scored_move.first;
    if (scored_move.first > max_score)
      max_score = scored_move.first;
  }

  for (auto scored_move : best_move.second)
    std::cout << (short)scored_move.second.src
              << "->"
              << (short)scored_move.second.dst
              << ", score: "
              << interpolate(scored_move.first, min_score, max_score, 0, 10)
              << std::endl;

  std::cout << (short)best_move.first.src
            << "->"
            << (short)best_move.first.dst
            << " was selected"
            << std::endl
            << std::endl;
}

