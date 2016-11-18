#ifndef INCLUDED__GAME_RULES_H
#define INCLUDED__GAME_RULES_H

#include "game-repr.h"

// Funkcje implementuj±ce ,,zasady gry''

namespace KIK {

// Czy mo¿na wykonaæ ruch 'm' na planszy 'board'
inline bool legalMove(const GameBoard& board, Move m)
{
      return m.x < board.width() && m.y < board.height() && board.at(m.x, m.y) == EmptyTile;
}

// Wygeneruj wszystkie mo¿liwe legalne ruchy
template <typename OutputIter>
void GenerateMoveList(const GameBoard& board, OutputIter out)
{
      for (int i = 0; i < board.height(); ++i)
            for (int j = 0; j < board.width(); ++j)
                  if (board.at(j, i) == EmptyTile)
                        *out++ = Move(j, i);
}


// Sprawd¼, czy wygra³ gracz 'player'
bool checkForWin(const GameBoard& board, playerT player);

// Koniec gry?
bool gameOver(const GameBoard& board);

}

#endif

