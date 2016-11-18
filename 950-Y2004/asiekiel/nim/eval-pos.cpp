#include "eval-pos.h"
#include "find-lines.h"
#include <config.h>
#include <algorithm>
#include <iostream>
#include <iterator>

namespace KIK {

namespace {
      
      // Funkcja pomocnicza -- szybkie podnoszenie do potêgi drugiej
      inline int pow2(int a, int n) { return a << (n - 1); }

      // Obiekt funkcyjny, który oblicza ocenê pozycji na podstawie obliczonych
      // wcze¶niej d³ugo¶ci linii.
      // Je¿eli znaleziono liniê o d³ugo¶ci wygrywaj±cej, to zwróæ WinningPosition.
      // W przeciwnym wypadku ocena jest sum± ocen za poszczególne liniê, gdzie linia
      // d³ugo¶ci n ma ocenê 4*(2^n).
      struct PositionEvaluator {
      private:
            int note;
      public:
            PositionEvaluator(): note(0) {}
            void operator()(int line_length) {
                  if (line_length == Config::winning_line_length)
                        note = WinningPosition;
                  else if (note < WinningPosition)
                        note += pow2(4, line_length);
            }
            operator int() { return note; }
      };
}

// Oblicz d³ugo¶ci linii u³o¿onych przez obydwu graczy. Je¿eli sytuacja na planszy
// jest wygrywaj±ca/przegrywaj±ca dla gracza aktualnie wykonuj±cego ruch, to
// poinformuj o tym zwracaj±c odpowiednio WinningPosition/LosingPosition.
// W przeciwnym wypadku ocena jest ró¿nic± punktów aktualnego gracza i przeciwnika.
int EvaluateStaticPosition(const GameBoard& board)
{
      std::vector<int> current, other;
      findLines(board, board.whoseTurn(), std::back_inserter(current));
      findLines(board, opponent(board.whoseTurn()), std::back_inserter(other));

      int cur_note   = std::for_each(current.begin(), current.end(), PositionEvaluator());
      int other_note = std::for_each(other.begin(), other.end(), PositionEvaluator());

      if (cur_note == WinningPosition)
              return WinningPosition;
      if (other_note == WinningPosition)
            return LosingPosition;
      return cur_note - other_note;
}

}
