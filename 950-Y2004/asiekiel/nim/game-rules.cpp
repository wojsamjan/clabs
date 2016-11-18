#include "game-rules.h"
#include "find-lines.h"
#include "config.h"
#include <algorithm>
#include <vector>
#include <iterator>

// Gracz wygra³, je¿eli u³o¿y³ liniê o wygrywaj±cej d³ugo¶ci
bool KIK::checkForWin(const GameBoard& board, playerT player)
{
      std::vector<int> v;
      findLines(board, player, std::back_inserter(v));
      std::vector<int>::const_iterator it =
            std::max_element(v.begin(), v.end());
      if (it == v.end())
            return false;
      else
            return *it >= Config::winning_line_length;
}

// Koniec, je¶li albo kto¶ wygra³, albo nie ma ju¿ mo¿liwych ruchów na planszy
bool KIK::gameOver(const GameBoard& board)
{
      return (board.turnsTaken() == board.width() * board.height()) ||
             checkForWin(board, Human) ||
             checkForWin(board, Computer);
}
