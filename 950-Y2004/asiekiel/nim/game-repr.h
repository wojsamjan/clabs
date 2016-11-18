#ifndef INCLUDED__GAME_H
#define INCLUDED__GAME_H

#include <vector>
#include <utility>
#include <iostream>

// Konkretna reprezentacja gry -- typy gracza, ruchu, pól.

namespace KIK {

enum playerT { Human, Computer };

inline playerT opponent(playerT player)
{
      switch (player) {
            case Human: return Computer;
            case Computer: return Human;
      }
      return Human;
}

enum tileT { HumanTile, ComputerTile, EmptyTile };

inline tileT tileOfPlayer(playerT player)
{
      switch (player) {
            case Human: return HumanTile;
            case Computer: return ComputerTile;
      }
      return EmptyTile;
}


class Move {
public:
      int x;
      int y;
      Move(int _x=0, int _y=0): x(_x), y(_y) {}
};

// Reprezentacja stanu gry -- tablicy pól. Dla wygody
// pamiêtamy wszystkie wykonywane ruchy.
class GameBoard {
      typedef std::vector< std::vector<tileT> > repr_type;
      typedef std::vector< std::pair<Move, playerT> > history_type;
      repr_type m_repr;
      history_type m_history;
      playerT m_whose_turn;
      playerT m_first_player;
public:
      GameBoard(int w, int h, playerT starting);
      int width() const            { return m_repr.empty() ? 0 : m_repr.begin()->size(); }
      int height() const           { return m_repr.size(); };
      int turnsTaken() const       { return m_history.size(); }
      playerT whoseTurn() const    { return m_whose_turn; }
      tileT at(int x, int y) const { return m_repr[y][x]; }
      Move lastMove() const        { return m_history.back().first; }
      void makeMove(Move m);
      void retractLastMove();
      void retractMove(Move m);
      void resize(int w, int h);
      void clean();
};

typedef GameBoard State;

// tylko do debugowania...
std::ostream& operator<<(std::ostream& os, playerT player);
std::ostream& operator<<(std::ostream& os, tileT tile);
std::ostream& operator<<(std::ostream& os, const GameBoard& board);

}

#endif

