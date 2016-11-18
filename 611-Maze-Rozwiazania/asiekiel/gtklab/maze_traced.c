#include "mazelib.h"
#include "direction_stack.h"
#include "maze_traced.h"
#include <unistd.h>
#include <stdio.h>

/* Implementacja jest bardziej skomplikowana, ni¿ by siê wydawa³o... */

bool maze_unsolved(void)
{
      return ds_empty();
}

bool maze_exit_found(void)
{
      return OutsideMaze(current_point_traced());
}

pointT current_point_traced(void)
{
      pointT temp;
      directionT dir;
      bool b;

      ds_top(&dir, &temp, &b);
      return temp;
}

static directionT next_dir(directionT dir)
{
      switch (dir) {
            case North: return East;
            case East: return South;
            case South: return West;
            case West: return West;
      }
      return North;
}

static bool first_good_direction(pointT pt, directionT base, directionT* res)
{
      while (WallExists(pt, base) || (!OutsideMaze(AdjacentPoint(pt, base)) && IsMarked(AdjacentPoint(pt, base)))) {
            if (base == West)
                  return false;
            else
                  base = next_dir(base);
      }
      *res = base;
      return true;
}

bool solve_maze_step(void)
{
      pointT temp, next;
      directionT dir, dir2;
      bool b;

      if (maze_unsolved() || maze_exit_found())
            return true;
      ds_top(&dir, &temp, &b);
      if (b) {
            UnmarkSquare(temp);
            ds_pop();
            return false;
      }
      MarkSquare(temp);
      if (!first_good_direction(temp, dir, &dir2)) {
            UnmarkSquare(temp);
            ds_pop();
      }
      else {
            if (dir2 == West)
                  ds_set_last_d_at_top(true);
            ds_set_dir_at_top(next_dir(dir2));
            next = AdjacentPoint(temp, dir2);
            ds_push(North, next, false);
      }
      return false;
}

void solve_maze_by_step_init(void)
{
      ds_push(North, GetStartPosition(), false);
}

void solve_maze_by_step_cleanup(void)
{
      ds_clear();
}
