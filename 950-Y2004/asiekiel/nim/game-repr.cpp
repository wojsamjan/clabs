#include "game-repr.h"
#include <algorithm>

namespace KIK {

GameBoard::GameBoard(int w, int h, playerT starting):
      m_repr(h, std::vector<tileT>(w)),
      m_whose_turn(starting),
      m_first_player(starting)
{
      this->clean();
}

void GameBoard::makeMove(Move m)
{
      m_repr[m.y][m.x] = tileOfPlayer(m_whose_turn);
      m_history.push_back(std::make_pair(m, m_whose_turn));
      m_whose_turn = opponent(m_whose_turn);
}

void GameBoard::retractLastMove()
{
      Move last = m_history.back().first;
      m_repr[last.y][last.x] = EmptyTile;
      m_whose_turn = opponent(m_whose_turn);
      m_history.pop_back();
}

void GameBoard::retractMove(Move m)
{
      m_repr[m.y][m.x] = EmptyTile;
      m_whose_turn = opponent(m_whose_turn);
}

void GameBoard::resize(int w, int h)
{
      m_repr.resize(h);
      for (repr_type::iterator it = m_repr.begin(); it != m_repr.end(); ++it)
            it->resize(w);
      this->clean();
}

void GameBoard::clean()
{
      for (repr_type::iterator it = m_repr.begin(); it != m_repr.end(); ++it)
            std::fill(it->begin(), it->end(), EmptyTile);
      m_history.clear();
      m_whose_turn = m_first_player;
}

std::ostream& operator<<(std::ostream& os, playerT player)
{
      switch (player) {
            case Human: os << "Human"; break;
            case Computer: os << "Computer"; break;
      }
      return os;
}

std::ostream& operator<<(std::ostream& os, tileT tile)
{
      switch (tile) {
            case HumanTile: os << 'o'; break;
            case ComputerTile: os << 'x'; break;
            case EmptyTile: os << ' '; break;
      }
      return os;
}

std::ostream& operator<<(std::ostream& os, const GameBoard& board)
{
      for (int i = 0; i < board.height(); ++i) {
            for (int j = 0; j < board.width(); ++j)
                  os << board.at(j, i) << ' ';
            os << '\n';
      }
      return os;
}

}
