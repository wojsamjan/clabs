#include "minimax.h"
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

namespace {

      int EvaluatePosition(State& state, int depth);

      Move DoFindBestMove(State& state, int depth, int& pRating)
      {
            std::vector<Move> possible_moves;
            GenerateMoveList(state, std::back_inserter(possible_moves));
            // Potasuj wygenerowane ruchy
            std::random_shuffle(possible_moves.begin(), possible_moves.end());
            int min_rating = WinningPosition + 1;
            Move best_move;
            for (std::vector<Move>::const_iterator it = possible_moves.begin();
                 it != possible_moves.end() && min_rating != LosingPosition; ++it) {
                  state.makeMove(*it);
                  int rating = EvaluatePosition(state, depth + 1);
                  ++evaluated_positions;
                  if (rating < min_rating) {
                        best_move = *it;
                        min_rating = rating;
                  }
                  state.retractLastMove();
            }
            pRating = -min_rating;
            return best_move;
      }

      int EvaluatePosition(State& state, int depth)
      {
            int rating;
            if (gameOver(state) || depth >= Config::max_recursion_depth)
                  return EvaluateStaticPosition(state);
            DoFindBestMove(state, depth, rating);
            return rating;
      }
}

int evaluated_positions = 0;

Move FindBestMove(State& state)
{
      int rating;
      evaluated_positions = 0;
      return DoFindBestMove(state, 0, rating);
}
