#ifndef INCLUDED__FIND_LINES_H
#define INCLUDED__FIND_LINES_H

#include <vector>
#include <iterator>
#include <iostream>
#include "game-repr.h"

// Obliczanie d³ugo¶ci u³o¿onych linii

namespace KIK {

namespace {
      // Struktura opisuj±ca kierunek ruchu
      struct MoveDirection {
            int dx;
            int dy;
      };

      // W tych kierunkach bêdziemy szukali linii
      MoveDirection directions[] = { {1,0}, {1,1}, {0,1}, {-1,1} };

      // Zwiêksz ruch (punkt) o wspó³rzêdne (dx, dy)
      inline Move& operator+=(Move& m, const MoveDirection& d) { m.x+=d.dx; m.y+=d.dy; return m; }

      // Sprawd¼, czy dany ruch znajduje siê wewn±trz planszy gry
      inline bool insideBoard(const Move& m, const GameBoard& b) { return m.x >= 0 && m.y >= 0 && m.x < b.width() && m.y < b.height(); }

      // Funkcja, która ma najwiêkszy wp³yw na wydajno¶æ ca³ego programu -- zlicz linie z³o¿one
      // ze znaczków 'tile' w kierunku 'd', d³ugo¶ci obliczonych linii zapisz na iterator 'out'
      template <typename OutputIter>
      void findLineInDirection(const GameBoard& board, const tileT tile,
                          const MoveDirection d, OutputIter out)
      {
            // tablica, w której pamiêtamy, czy dany punkt ju¿ odwiedzili¶my
            std::vector<bool> used_tiles(board.width() * board.height());

            // dla wszystkich punktów na planszy: próbuj i¶æ jak najdalej siê da
            // w kierunku wyznaczonym przez 'd', zaznaczaj±c zliczane pozycje.
            // Omijaj pola ju¿ odwiedzone.
            for (int i = 0; i < board.height(); ++i)
                  for (int j = 0; j < board.width(); ++j) {
                        Move m(j, i);
                        if (used_tiles[m.y*board.width() + m.x] == false) {
                              int line_length = 0;
                              while (insideBoard(m, board) && board.at(m.x, m.y) == tile) {
                                    used_tiles[m.y*board.width() + m.x] = true;
                                    ++line_length;
                                    m += d;
                              }
                              if (line_length > 1) {
                                    *out = line_length;
                                    ++out;
                              }
                        }
                  }
      }

}

// Zlicz wszystkie linie utworzone przez gracza 'player'
template <typename OutputIter>
void findLines(const GameBoard& board, playerT player, OutputIter it)
{
      tileT tile = tileOfPlayer(player);
      for (int i = 0; i < 4; ++i)
            findLineInDirection(board, tile, directions[i], it);
}

}

#endif

